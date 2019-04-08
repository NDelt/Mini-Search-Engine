# Mini Search Engine
<img src="https://img.shields.io/badge/version-0.1.0-blue.svg" alt="image" />

역색인 테이블 기반 검색 엔진

### 개발 환경
* [JetBrains CLion](https://www.jetbrains.com/clion/?fromMenu)
* Windows Subsystem for Linux - Ubuntu
* GCC 7.3.0
* CMake 3.10.2
* Redis

### 시작하기
#### (1) Redis 설치하기
```
sudo apt -y update
sudo apt -y install redis-server
sudo service redis-server start
service redis-server status
redis-server -version
redis-cli
```
#### (2) Redis++ 라이브러리 설치하기
* [GitHub Repository: sewenew/redis-plus-plus](https://github.com/sewenew/redis-plus-plus)
#### (3) 바이너리 사용하기
```
git clone git@github.com:NDelt/Mini-SearchEngine.git
cd resources
```
