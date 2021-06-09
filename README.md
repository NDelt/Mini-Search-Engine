# Mini Search Engine

<img src="https://img.shields.io/badge/version-1.0.0-blue.svg" alt="image" />

역색인 테이블 기반 검색 엔진

## 개발 환경

* [JetBrains CLion](https://www.jetbrains.com/clion/?fromMenu)
* CMake 3.16 ~ 3.17

## 사용하기
1. 프로젝트 폴더로 이동
```
cd mini-search-engine/
```
2. 빌드 스크립트 생성
```
cmake .
```
3. 빌드
* Linux
```
make all
```
* Windows
```
devenv .\Mini-Search-Engine-Cpp.sln /build Debug
```
4. 바이너리 폴더로 이동
* Linux
```
cd output/
```
* Windows
```
cd Debug/
```
5. 바이너리 실행
* Linux
```
./mini-search-engine
```
* Windows
```
.\mini-search-engine.exe
```

약 10초 간의 인덱싱 작업(WSL Ubuntu 20.04 기준) 후 검색어 입력(ex: golang, hadoop, aws azure, spark, ...)

* 입력한 검색어를 포함하는 CSV 파일의 레코드 ID를 오름차순으로 출력
* 여러 단어로 된 검색어를 입력했을 경우, 공통 ID를 우선하여 출력

## 클래스 구조

![alt text](resources/arch.PNG)

## 사용 예시

![alt text](resources/example.gif)

