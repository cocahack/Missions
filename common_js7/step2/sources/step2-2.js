const { pow, PI } = Math;
const callHistory = [];

function printExecutionSequence(){
  console.log('계산수행순서: ' + callHistory.join(' '));
}

function make2dArray(h, w, val = 0){
  var arr = [];
  for(let i = 0; i < h; i++) {
      arr[i] = [];
      for(let j = 0; j < w; j++) {
          arr[i][j] = val;
      }
  }
  return arr;
}

function circle(radius) {
    callHistory.push('circle');
    return pow(radius, 2) * PI;
};

function rect(width, height) {
    callHistory.push('rect');
    return width * height;
};

function trapezoid(line1, line2, height) {
    callHistory.push('trapezoid');
    return 2 * height * (line1 + line2);
};

const circumference = radius => 2 * radius * PI;

function cylinder(radius, height){
  callHistory.push('cylinder');
  return 2 * circle(radius) + circumference(radius) * height;
}

function recursiveArea(type, args){
  
}

function recursiveCircle(startRadius, endRadius = startRadius) {
    return circle(startRadius) + (startRadius === endRadius ? 0 : recursiveCircle(startRadius+1, endRadius));
} 



function recursiveRect(startWidth, 
                       startHeight, 
                       endWidth = startWidth, 
                       endHeight = startHeight){
  let cache = make2dArray(endWidth + 1, endHeight + 1, -1);
  function recursiveRectInner(startWidth, startHeight, endWidth, endHeight){
    if(startWidth > endWidth || startHeight > endHeight) {
      return 0;
    }
    if(cache[startWidth][startHeight] !== -1) {
      return cache[startWidth][startHeight];
    }
    return cache[startWidth][startHeight] = rect(startWidth, startHeight) +
                                            recursiveRectInner(startWidth + 1, startHeight, endWidth, endHeight) +
                                            recursiveRectInner(startWidth, startHeight + 1, endWidth, endHeight)
  }
  return recursiveRectInner(startWidth, startHeight, endWidth, endHeight);
}

function getArea(type, ...args) {
    let result
    switch (type) {
        case 'circle': 
            result = recursiveCircle(args[0], args[1])  
            break;
        case 'rect': 
            result = recursiveRect(args[0], args[1], args[2], args[3]);
            break;
        case 'trapezoid': 
            trapezoid(num)
            break;
    };
    return result;
};