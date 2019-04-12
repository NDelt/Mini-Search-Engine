# -*- coding: utf-8 -*-
import re
import sys
import threading
from datetime import *
from random import *
from urllib.parse import urlparse

import pymysql
from bs4 import BeautifulSoup
from selenium import common, webdriver

seed(datetime.now())
sys.setrecursionlimit(5000)

follow_ex_counter = 0
follow_in_counter = 0

# 크롬드라이버의 옵션 설정
options = webdriver.ChromeOptions()
options.add_argument("headless")
options.add_argument("window-size=1920x1080")
options.add_argument("user-agent=Chrome/72.0.3626.81")

# 셀레니엄 드라이버의 경로를 크롬드라이버로 설정
driver = webdriver.Chrome("", options=options)
driver.implicitly_wait(3)

conn = pymysql.connect(host="127.0.0.1", user="root", passwd="", db="", charset="utf8mb4")
cur = conn.cursor()

lock = threading.Lock()

init = ["https://stackoverflow.com/", "https://en.cppreference.com/w/", "https://namu.wiki/w/"]


def add_external_links(bs_obj, scheme, netloc):
    """
    이 함수는 웹 페이지 내에 존재하는 외부 링크를 탐색하므로, 현재 페이지의 도메인이 들어 있는 netloc의 값은 배제되어야 한다.
    """
    for link in bs_obj.find_all("a", href=re.compile("^(https|http|www|\/\/)((?!" + netloc + ").)*$")):
        if link.attrs["href"] is None:
            continue
        
        link.attrs["href"] = reassemble_address(scheme, link.attrs["href"])
        
        lock.acquire()
        select_ex_return = cur.execute("SELECT * FROM external_links WHERE url=%s;", (link.attrs["href"]))
        select_em_return = cur.execute("SELECT * FROM empty_or_error_links WHERE url=%s;", (link.attrs["href"]))
        lock.release()
        
        if select_ex_return == 0 and select_em_return == 0:  # 쿼리문에 해당하는 레코드의 개수가 0일 때
            try:
                driver.get(link.attrs["href"])
                html_tb = driver.page_source
                bs_obj_sub = BeautifulSoup(html_tb, "html.parser")
                
                title = bs_obj_sub.find("title")
                body = bs_obj_sub.find("body")
                # 탐색한 링크에 미리 접속하여 해당 페이지의 title 태그와 body 태그의 값을 받아온다.
                
                if title is None:
                    continue
                elif len(title) > 255:
                    title = title[:255]
            
            except (AttributeError, common.exceptions.WebDriverException) as e:
                add_empty_or_error_links(link.attrs["href"])
                print("##### " + link.attrs["href"] + " -> ", end="")
                print(e, end="")
                print(". Skipping...")
                continue
            
            lock.acquire()
            cur.execute("INSERT INTO external_links (id, url, title, contents) VALUES (%s, %s, %s, %s);",
                        (0, link.attrs["href"], title.get_text(), body.get_text()))
            conn.commit()
            lock.release()
            
            print("--> ", end="")
            print(threading.current_thread().getName(), end=", ")
            print(link.attrs["href"], end=": ")
            print("Link added to database.")


def add_internal_links(bs_obj, scheme, netloc):
    """
    내부 링크의 맨 앞에는 상대 주소를 표현하기 위한 '/'가 올 수도 있고, 일반적인 URI처럼 https나 http, //, 또는 www가 올 수도 있다.
    따라서 아래와 같은 정규 표현식으로 모든 경우를 탐색한다.
    """
    for link in bs_obj.find_all("a", href=re.compile("^(\/|.*" + netloc + ").*")):
        if link.attrs["href"] is None:
            continue
        
        if not link.attrs["href"].startswith("//") and link.attrs["href"].startswith("/"):  # 링크가 단일 '/' 문자로 시작할 경우 별도로 처리한다.
            link.attrs["href"] = scheme + "://" + netloc + link.attrs["href"]
            if "www" in link.attrs["href"]:
                link.attrs["href"] = link.attrs["href"].replace("www.", "")
            if link.attrs["href"].endswith("/"):
                link.attrs["href"] = link.attrs["href"][:-1]
        else:
            link.attrs["href"] = reassemble_address(scheme, link.attrs["href"])
        
        lock.acquire()
        select_in_return = cur.execute("SELECT * FROM internal_links WHERE url=%s;", (link.attrs["href"]))
        select_em_return = cur.execute("SELECT * FROM empty_or_error_links WHERE url=%s;", (link.attrs["href"]))
        lock.release()
        
        if select_in_return == 0 and select_em_return == 0:
            try:
                driver.get(link.attrs["href"])
                html_tb = driver.page_source
                bs_obj_sub = BeautifulSoup(html_tb, "html.parser")
                
                title = bs_obj_sub.find("title")
                body = bs_obj_sub.find("body")
                
                if title is None:
                    continue
                elif len(title) > 255:
                    title = title[:255]
            
            except (AttributeError, common.exceptions.WebDriverException) as e:
                add_empty_or_error_links(link.attrs["href"])
                print("##### " + link.attrs["href"] + " -> ", end="")
                print(e, end="")
                print(". Skipping...")
                continue
            
            lock.acquire()
            cur.execute("INSERT INTO internal_links (id, url, title, contents) VALUES (%s, %s, %s, %s);",
                        (0, link.attrs["href"], title.get_text(), body.get_text()))
            conn.commit()
            lock.release()
            
            print("--> ", end="")
            print(threading.current_thread().getName(), end=", ")
            print(link.attrs["href"], end=": ")
            print("Link added to database.")


def add_empty_or_error_links(href):
    """
    외부, 내부 링크가 하나도 없거나 접속 시 에러가 발생하는 페이지의 링크를 저장한다.
    """
    lock.acquire()
    select_return = cur.execute("SELECT * FROM empty_or_error_links WHERE url=%s;", href)
    
    if select_return == 0:
        cur.execute("INSERT INTO empty_or_error_links (id, url) VALUES (%s, %s);", (0, href))
        conn.commit()
    
    lock.release()


def reassemble_address(scheme, href):
    # 각기 다르게 표현되는 URI를 비교하기 위해, 프로토콜(https:// 또는 http:// 또는 //)과 호스트(www.)를 URI에서 제거한다.
    if href.startswith("//"):
        href = href[2:]
        if "www" in href:
            href = href.replace("www.", "")
    elif "https" in href:
        href = href.replace("https://", "")
        if "www" in href:
            href = href.replace("www.", "")
    elif "http" in href:
        href = href.replace("http://", "")
        if "www" in href:
            href = href.replace("www.", "")
    elif "www" in href:
        href = href.replace("www.", "")
    
    # URI 끝의 Trailing slash를 제거한다.
    if href.endswith("/"):
        href = href[:-1]
    
    # 조각난 href 속성의 값을 재조립한다.
    href = scheme + "://" + href
    
    return href


# ------------------------------- Deprecated ------------------------------- #
def split_address(addr):
    address_parts = None
    
    if addr.startswith("//"):  # '//'로 시작하는 링크일 때
        address_parts = addr[2:].split("/")
        if "www" in address_parts[0]:
            address_parts = address_parts[0].replace("www.", "")
    elif "https" in addr:  # 'https://'로 시작하는 링크일 때
        address_parts = addr.replace("https://", "").split("/")
        if "www" in address_parts[0]:
            address_parts = address_parts[0].replace("www.", "")
    elif "http" in addr:  # 'http://'로 시작하는 링크일 때
        address_parts = addr.replace("http://", "").split("/")
        if "www" in address_parts[0]:
            address_parts = address_parts[0].replace("www.", "")
    elif "www" in addr:  # 'www'로 시작하는 링크일 때
        address_parts = addr.replace("www.", "").split("/")
    
    return address_parts  # 프로토콜과 호스트가 제거된 도메인 리스트를 반환한다.


def get_random_external_links(starting_page):
    try:
        driver.get(starting_page)
        html = driver.page_source
        bs_obj = BeautifulSoup(html, "html.parser")
        title = bs_obj.find("title")
        print("(Current) ", end="")
        print(title.get_text(), end=":\n")
    except (AttributeError, common.exceptions.WebDriverException) as e:
        add_empty_or_error_links(starting_page)
        print("##### " + starting_page + " -> ", end="")
        print(e, end="")
        print(". Search again...")
        print("--------------------------------------------------")
        return -1
    
    scheme = urlparse(starting_page).scheme
    netloc = urlparse(starting_page).netloc
    
    if "www" in netloc:
        netloc = netloc.replace("www.", "")
        # 호스트(www.)가 있는 링크와 없는 링크를 모두 찾기 위해, 탐색 시 비교 대상이 될 URI의 netloc에서 호스트를 제거한다.
    
    add_external_links(bs_obj, scheme, netloc)
    
    lock.acquire()
    select_ex_return = cur.execute("SELECT * FROM external_links;")
    lock.release()
    
    """
    외부 링크를 저장하는 데이터베이스가 비어 있을 경우, 현재 페이지와 도메인이 동일한 내부 링크를 탐색한다.
    """
    if select_ex_return == 0:
        print("No external links, looking around internal link.")
        
        add_internal_links(bs_obj, scheme, netloc)
        # 현재 페이지를 기준으로 내부 링크를 탐색하고 데이터베이스에 저장한다.
        
        lock.acquire()
        select_in_return = cur.execute("SELECT * FROM internal_links;")
        lock.release()
        
        if select_in_return == 0:
            add_empty_or_error_links(starting_page)
            return -1  # 내부 링크도 존재하지 않는다면 탐색을 종료한다.
        else:
            lock.acquire()
            cur.execute("SELECT url FROM internal_links ORDER BY RAND() LIMIT 1;")  # 내부 링크 중 하나를 무작위로 조회한다.
            lock.release()
            
            fetch = cur.fetchall()
            selected_tuple = str(fetch[0][0])
            # 변수에 fetch에 반환되는 값은 DB 쿼리 결과를 담은 다중 튜플이다. 이 튜플은 ((쿼리 결과), (쿼리 결과), ...)의 형식으로 이루어져 있다.(LIMIT의 값이 2 이상일 경우)
            # 여기서는 하나의 쿼리 결과, 그 중에서도 url 레코드의 값만 전달받으므로 반환되는 튜플은 ((b'url',),)의 형식이다.(b'...'는 BLOB 타입 레코드의 데이터를 의미)
            # 실제 구하고자 하는 url은 이 다중 튜플의 첫 번째 튜플에서 첫 번째 원소를 추출한 값이고, 문자열로 조작이 가능하도록 해당 값을 문자열 변환 함수 str()의 인자로 전달한다.
            # 따라서 이를 식으로 표현하면 "str(fetch[0][0])"이 된다.
            
            if selected_tuple.startswith("b'"):
                selected_tuple = selected_tuple[2:]
            
            if selected_tuple.endswith("'"):
                selected_tuple = selected_tuple[:-1]
            
            return selected_tuple
    
    else:
        lock.acquire()
        cur.execute("SELECT url FROM external_links ORDER BY RAND() LIMIT 1;")  # 외부 링크 중 하나를 무작위로 조회한다.
        lock.release()
        
        fetch = cur.fetchall()
        selected_tuple = str(fetch[0][0])
        
        if selected_tuple.startswith("b'"):
            selected_tuple = selected_tuple[2:]
        
        if selected_tuple.endswith("'"):
            selected_tuple = selected_tuple[:-1]
        
        return selected_tuple


def get_random_internal_links(starting_page):
    try:
        driver.get(starting_page)
        html = driver.page_source
        bs_obj = BeautifulSoup(html, "html.parser")
        title = bs_obj.find("title")
        print("(Current) ", end="")
        print(title.get_text(), end=":\n")
    except (AttributeError, common.exceptions.WebDriverException) as e:
        add_empty_or_error_links(starting_page)
        print("##### " + starting_page + " -> ", end="")
        print(e, end="")
        print(". Search again...")
        print("--------------------------------------------------")
        return -1
    
    scheme = urlparse(starting_page).scheme
    netloc = urlparse(starting_page).netloc
    
    if "www" in netloc:
        netloc = netloc.replace("www.", "")  # 도메인에 'www.' 호스트가 포함되어 있으면 제거한다.
    
    add_internal_links(bs_obj, scheme, netloc)
    # 현재 페이지를 기준으로 내부 링크를 탐색하고 데이터베이스에 저장한다.
    
    lock.acquire()
    select_return = cur.execute("SELECT * FROM internal_links;")
    lock.release()
    
    if select_return == 0:
        add_empty_or_error_links(starting_page)
        return -1
    else:
        lock.acquire()
        cur.execute("SELECT url FROM internal_links ORDER BY RAND() LIMIT 1;")  # 내부 링크 중 하나를 무작위로 조회한다.
        lock.release()
        
        fetch = cur.fetchall()
        selected_tuple = str(fetch[0][0])
        
        if selected_tuple.startswith("b'"):
            selected_tuple = selected_tuple[2:]
        
        if selected_tuple.endswith("'"):
            selected_tuple = selected_tuple[:-1]
        
        return selected_tuple


def follow_external_first(initial_page):
    global follow_ex_counter
    
    get_link = get_random_external_links(initial_page)  # 임의의 외부 링크를 탐색한다.
    
    if get_link == -1:
        print("Error code(-1) is returned. Search again...")
        print("--------------------------------------------------")
        return follow_external_first(initial_page)  # 인자에 저장된 주소로 재귀 호출
    
    print("* Random external link is: {}".format(get_link))
    print("--------------------------------------------------")
    
    if follow_ex_counter <= 5000:
        follow_ex_counter += 1
        return follow_external_first(get_link)  # get_link에 반환된 주소로 재귀 호출
    else:
        follow_ex_counter = 0
        print("We can't do recursion anymore. Quit searching...")
        print("--------------------------------------------------")
        return


def follow_internal(initial_page):
    global follow_in_counter
    
    get_link = get_random_internal_links(initial_page)  # 임의의 내부 링크를 탐색한다.
    
    if get_link == -1:
        print("Error code(-1) is returned. Search again...")
        print("--------------------------------------------------")
        return follow_internal(initial_page)  # 인자에 저장된 주소로 재귀 호출
    
    print("* Random internal link is: {}".format(get_link))
    print("--------------------------------------------------")
    
    if follow_in_counter <= 5000:
        follow_in_counter += 1
        return follow_internal(get_link)  # get_link에 반환된 주소로 재귀 호출
    else:
        follow_in_counter = 0
        print("We can't do recursion anymore. Quit searching...")
        print("--------------------------------------------------")
        return


ExternalThread = threading.Thread(target=follow_external_first, args=(init[randint(0, len(init) - 1)],), name="ExternalThread")
InternalThread = threading.Thread(target=follow_internal, args=(init[randint(0, len(init) - 1)],), name="InternalThread")
# 외부 링크를 탐색하는 쓰레드와 내부 링크를 탐색하는 쓰레드를 별도로 생성하여 각각 동작하게 한다.

ExternalThread.start()
InternalThread.start()

ExternalThread.join()
InternalThread.join()
cur.close()
# 두 쓰레드가 작업을 모두 완료할 때까지 기다린 후 데이터베이스 연결을 종료한다.
