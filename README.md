# Mini Search Engine
<img src="https://img.shields.io/badge/version-0.1.0-blue.svg" alt="image" />

역색인 테이블 기반 검색 엔진

### 개발 환경
* [JetBrains CLion](https://www.jetbrains.com/clion/?fromMenu)
* Windows Subsystem for Linux - Ubuntu 18.04
* GCC 7.3.0
* CMake 3.10.2

### 사용하기
```
- Fork repository(우측 상단의 'Fork' 버튼 클릭)
- git clone git@github.com:(Username)/Mini-SearchEngine.git
- sudo chmod -R 755 Mini-SearchEngine/
- cd cmake-build-release-wsl/
- ./main
- 인덱싱(약 20초 소요) 완료 후 검색어 입력(ex: golang, hadoop, haskell code, spark, ...)
>> 입력한 검색어를 포함하는 CSV 파일의 레코드 ID를 오름차순으로 출력
>> 여러 단어로 된 검색어를 입력했을 경우, 공통 ID를 우선하여 출력
```
