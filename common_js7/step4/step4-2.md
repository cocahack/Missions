# Step 4-2. 비동기 프로그래밍

## 동기와 비동기에서 Call Stack 탐색

### 동기

```javascript
const baseData = [1,2,3,4,5,6,100];

function foo() {
  baseData.forEach((v,i) => {
    console.log("sync ", i);
    bar();
  });
}

function bar() {
  baseData.forEach((v,i) => {
    console.log("sync 2", i);
  });
}

foo();
```

코드를 실행하면 `foo` 내부에서 `baseData` 의 요소를 하나씩 순회하면서 `bar` 함수를 호출하게 될 것이다. 따라서 출력되는 결과는 항상 아래처럼 나올 것이다.

```console
$ node test.js
sync  0
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
sync 2 5
sync 2 6
sync  1
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
sync 2 5
sync 2 6
sync  2
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
...
```

Call stack을 그림으로 나타내면 다음과 같다. `foo` 에서 `forEach` 로 배열을 순회하면서 `bar` 함수를 반복적으로 호출하게 된다. 

<img width="986" alt="image-20190416113745820" src="https://user-images.githubusercontent.com/18232901/56178168-34b39780-603c-11e9-8e5b-eb5e33ca889e.png">



### 비동기

자바스크립트는 하나의 스레드만 사용할 수 있다. 이는 Call stack을 한 개만 가지고 있고 한 번에 하나의 작업만 할 수 있다는 뜻이다.

#### Blocking / Non-blocking

Node.js에서 **Blocking** 은 is 자바스크립트 이외의 연산(IO 등)이 끝날 때 까지 기다린 후에 Node.js 프로세스의 자바스크립트 코드를 실행하는 것을 말한다. 



#### 중첩된 setTimeout

```javascript
const baseData = [1,2,3,4,5,6,100];

const asyncRun = (arr, fn) => {
   arr.forEach((v,i) => {
     setTimeout(() => {
       setTimeout(() => {
         console.log("cb 2");
         fn(i)
        },1000);
       console.log("cb 1");
     }, 1000);
   });
}

asyncRun(baseData, idx =>console.log(idx))
```

위의 코드에 대한 call stack 및 callback queue의 변화를 그림으로 나타내었다.

![nested_setTimeout](https://user-images.githubusercontent.com/18232901/56184966-fecfdc80-6056-11e9-8e26-edcd60ed660a.gif)

