# Mini Search Engine (C++)
<img src="https://img.shields.io/badge/version-1.0.0-blue.svg" alt="image" />

역색인 테이블 기반 검색 엔진 (C++)

### 개발 환경
* [JetBrains CLion](https://www.jetbrains.com/clion/?fromMenu)
* Windows Subsystem for Linux - Ubuntu 18.04
* g++ 7.4.0
* CMake 3.10.2

### 사용하기
```
- Fork repository(우측 상단의 'Fork' 버튼 클릭)
- git clone git@github.com:(Username)/Mini-SearchEngine.git
- sudo chmod -R 755 Mini-SearchEngine/
- cd cmake-build-debug-wsl/
- ./main
- 인덱싱 완료 후 검색어 입력(ex: golang, hadoop, aws azure, spark, ...)
>> 입력한 검색어를 포함하는 CSV 파일의 레코드 ID를 오름차순으로 출력
>> 여러 단어로 된 검색어를 입력했을 경우, 공통 ID를 우선하여 출력
```

### 클래스 구조
![alt text](resources/arch.PNG)

### 사용 예시
![alt text](resources/example.gif)

### 참고 문서
* [구글 검색 엔진의 해부학](http://www.emh.co.kr/content.pl?google_search_engine)
* [나는 왜 루씬을 C++로 재작성했는가?](https://deview.kr/data/deview/2019/presentation/[145]%EB%82%98%EB%8A%94%20%EC%99%9C%20%EB%A3%A8%EC%94%AC%EC%9D%84%20C++%EB%A1%9C%20%EC%9E%AC%EC%9E%91%EC%84%B1%ED%96%88%EB%8A%94%EA%B0%80.pdf)
