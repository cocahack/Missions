module.exports.isObject = value => value && 
                                   typeof value === 'object' && 
                                   value.constructor === Object;

module.exports.isNumber = value => typeof value === 'number';