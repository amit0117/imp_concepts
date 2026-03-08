function introduction(city, country, hobby = null) {
  console.log(
    `Hi,\nMy name is ${this.name}, and I'm ${this.age} years old.\nI am from ${city} city, ${country} country.\nMy hobby is ${hobby}.\n`,
  );
}
// introduction()
const a = { name: "Amit", age: 24 };
const b = { name: "Ankush", age: 20 };
const city = "Daudnagar";
const country = "India";
const myhobby = "dancing";

// const bindedFunction=introduction.bind(a)
// bindedFunction(city,country,myhobby)

// introduction.call(a,city,country,myhobby)

// introduction.apply(a,[city,country,myhobby])

Function.prototype.myBind = function (obj, ...firstArgs) {
  obj = obj || globalThis;

  const thisForFunctionBinding = this; // beacause when we all something . object and if we have this, then in that case that 'this' points to the object
  if (typeof thisForFunctionBinding !== "function")
    throw new Error("here this must be of type of function");
  return function (...newArgs) {
    // will do the function.apply
    return thisForFunctionBinding.apply(obj, [...firstArgs, ...newArgs]);
  };
};

// const customBinded=introduction.myBind(b,city,country);
// customBinded(myhobby)

Function.prototype.myCall = function (objContext, ...args) {
  if (typeof this !== "function")
    throw new Error("this must be of function type");
  // if we don't want to add this to any object then we will add this to the global object (irrespective of browser and server)
  const tempSymbol = Symbol("function");
  objContext[tempSymbol] = this;

  const result = objContext[tempSymbol](...args);
  delete objContext[tempSymbol];
  return result;
};

introduction.myCall(b, city, country, myhobby);

Function.prototype.myApply = function (objContext, ...args) {
  if (typeof this !== "function")
    throw new Error("this must be a type of function");

  objContext = objContext || globalThis;

  const tempSymbol = Symbol();
  objContext[tempSymbol] = this;
  const result = objContext[tempSymbol](...args);
  delete objContext[tempSymbol];
  return result;
};

introduction.myApply(a, city, country, myhobby);
