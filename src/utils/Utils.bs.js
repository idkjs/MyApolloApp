// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";

var ReasonPromise = {};

function then_(promise, f) {
  return promise.then(Curry.__1(f));
}

function ignore(prim) {
  
}

var $$Promise = {
  then_: then_,
  ignore: ignore
};

export {
  ReasonPromise ,
  $$Promise ,
  
}
/* No side effect */