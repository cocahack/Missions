const myReduce = (arr, callback, initialValue) => {
  let ret = (initialValue === undefined ? arr[0] : initialValue);
  for(let idx = (initialValue === undefined ? 1 : 0);
      idx < arr.length;
      idx++){
        if(arr[idx] === undefined) continue;
        ret = callback(ret, arr[idx]);
      }
  return ret;
}

let arr = [1,2,3,4,5];
let arr2 = [-15,7,3,0,5];
let arr3 = ["DP", "Greedy", "disjoint set", "trie", "Segment tree"];

const addCallBack = (acc, cur) => acc += cur;
const maxCallBack = (acc, cur) => Math.max(acc, cur);
const pushElementAfterIncr = (acc, cur) => { acc.push(cur + 1); return acc;}
const joinString = (acc, cur) => acc += cur + " ";


// Task #1 모든 요소 더하기
console.log(myReduce(arr, addCallBack)); 

// Task #2 최댓값 구하기
console.log(myReduce(arr2, maxCallBack));

// Task #3 각 요소를 1씩 더한 결과 반환하기(map 흉내내기)
console.log(myReduce(arr2, pushElementAfterIncr, []));

// Array.prototype.reduce에서 초기값을 설정하지 않으면 배열의 첫번째 요소를 사용하는지 검증.
// Task #4 초기값이 없을 경우 에러 발생. 
try{
  console.log(myReduce(arr2, pushElementAfterIncr));
} catch (err) { 
  console.log(err.message); 
}
try{
  console.log(arr2.reduce(pushElementAfterIncr)); 
} catch(err) { 
  console.log(err.message); 
}

// Task #5 초기값이 없을 경우 의도하지 않은 결과 반환
console.log(myReduce(arr3, joinString));
console.log(arr3.reduce(joinString));
console.log(myReduce(arr3, joinString, ""));
