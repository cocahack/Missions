const { mission1Data } = require('./data');
const { isObject, isNumber } = require('./util');

function getKeysHaveNumType(obj) {
  const ret = [];
  (function findKeyRecur(obj) {
    for(let key in obj){
      if(isObject(obj[key])) {
         findKeyRecur(obj[key]);
      }
      else {
        if(isNumber(obj[key])){
          ret.push(key);
        }
      }
    }
  })(obj);
  return ret;
}

console.log(getKeysHaveNumType(mission1Data));