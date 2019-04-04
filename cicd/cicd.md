# CI/CD 실습



## Ubuntu Container 생성

[groomide](https://ide.goorm.io/) 가입 후 대시보드에서 컨테이너 생성(Blank 16.04 선택)

![스크린샷 2019-04-03 오전 10.02.31](/Users/mcc/Desktop/스크린샷 2019-04-03 오전 10.02.31.png)



대시보드에서 생성된 컨테이너를 실행하고 ide에서 SSH 커맨드와 비밀번호를 복사하여 터미널로 접속

![image-20190403100706343](/Users/mcc/Library/Application Support/typora-user-images/image-20190403100706343.png)



## 자바 설치

OpenJDK 8 설치

```console
root@goorm:~# apt-get install openjdk-8-jdk
...
root@goorm:~# java -version
openjdk version "1.8.0_191"
OpenJDK Runtime Environment (build 1.8.0_191-8u191-b12-2ubuntu0.16.04.1-b12)
OpenJDK 64-Bit Server VM (build 25.191-b12, mixed mode)
```

