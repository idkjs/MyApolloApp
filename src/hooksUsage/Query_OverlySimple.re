open ReactNative;
module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        id
        text
        completed
      }
    }
  |}
];

[@react.component]
let make = () => {
  switch (TodosQuery.use()) {
  | {loading: true} =><Text> "Loading..."->React.string </Text>
  | {error: Some(_error)} => <Text>"Error loading data"->React.string </Text>
  | {data: Some({todos})} =>
    <Text>
      "There are "->React.string
      {todos->Belt.Array.length->React.int}
      " To-Dos"->React.string
    </Text>
  | {data: None, error: None, loading: false} =>
    <Text>"I hope this is impossible, but sometimes it's not!"->React.string</Text>
  };
};
