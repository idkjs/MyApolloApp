// Generated by ReScript, PLEASE EDIT WITH CARE

import * as ApolloClient__React_Hooks_UseQuery from "reason-apollo-client/src/@apollo/client/react/hooks/ApolloClient__React_Hooks_UseQuery.bs.js";

var Raw = {};

var query = (require("@apollo/client").gql`
  fragment TodoItem on TodoItem   {
    __typename
    id
    text
    completed
  }
`);

function parse(value) {
  var value$1 = value.completed;
  return {
          __typename: value.__typename,
          id: value.id,
          text: value.text,
          completed: !(value$1 == null) ? value$1 : undefined
        };
}

function serialize(value) {
  var value$1 = value.completed;
  var completed = value$1 !== undefined ? value$1 : null;
  var value$2 = value.text;
  var value$3 = value.id;
  var value$4 = value.__typename;
  return {
          __typename: value$4,
          id: value$3,
          text: value$2,
          completed: completed
        };
}

function verifyArgsAndParse(_TodoItem, value) {
  return parse(value);
}

function verifyName(param) {
  
}

var TodoItem = {
  Raw: Raw,
  query: query,
  parse: parse,
  serialize: serialize,
  verifyArgsAndParse: verifyArgsAndParse,
  verifyName: verifyName
};

var Raw$1 = {};

var query$1 = ((frag_0) => require("@apollo/client").gql`
  query Fragments  {
    allTodos  {
      ...TodoItem
    }
  }
  ${frag_0}
`)(query);

function parse$1(value) {
  var value$1 = value.allTodos;
  return {
          allTodos: value$1.map(parse)
        };
}

function serialize$1(value) {
  var value$1 = value.allTodos;
  var allTodos = value$1.map(serialize);
  return {
          allTodos: allTodos
        };
}

function serializeVariables(param) {
  
}

function makeVariables(param) {
  
}

function makeDefaultVariables(param) {
  
}

var Fragments_inner = {
  Raw: Raw$1,
  query: query$1,
  parse: parse$1,
  serialize: serialize$1,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  makeDefaultVariables: makeDefaultVariables
};

var include = ApolloClient__React_Hooks_UseQuery.Extend({
      query: query$1,
      Raw: Raw$1,
      parse: parse$1,
      serialize: serialize$1,
      serializeVariables: serializeVariables
    });

var Fragments_refetchQueryDescription = include.refetchQueryDescription;

var Fragments_use = include.use;

var Fragments_useLazy = include.useLazy;

var Fragments_useLazyWithVariables = include.useLazyWithVariables;

var Fragments = {
  Fragments_inner: Fragments_inner,
  Raw: Raw$1,
  query: query$1,
  parse: parse$1,
  serialize: serialize$1,
  serializeVariables: serializeVariables,
  makeVariables: makeVariables,
  makeDefaultVariables: makeDefaultVariables,
  refetchQueryDescription: Fragments_refetchQueryDescription,
  use: Fragments_use,
  useLazy: Fragments_useLazy,
  useLazyWithVariables: Fragments_useLazyWithVariables
};

export {
  TodoItem ,
  Fragments ,
  
}
/* query Not a pure module */
