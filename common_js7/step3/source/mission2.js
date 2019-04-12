const { mission2Data } = require('./data');

const checkTypeIsSk = obj => obj.type === 'sk';

const parsedData = JSON.parse(mission2Data);

function getAllNameHaveSkType (jsonArray){
  const ret = [];
  (function findNameRecur(arr){
    if(arr === undefined) return;
    arr.forEach(element => {
      if(checkTypeIsSk(element)){
        ret.push(element.name);
      }
      findNameRecur(element.childnode);
    });
  })(jsonArray);
  return ret;
}

console.log(getAllNameHaveSkType(parsedData));