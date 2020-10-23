// The TodosQuery below is going to look for a module of the same name to define the fragment
open ReactNative;
module TodoItem = Fragments.TodoItem;

module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        # This references the TodoItem fragment definition module above!
        ...TodoItem
      }
    }
  |}
];

// It's easy to share types when using Fragments
module TodoCount = {
  [@react.component]
  let make = (~todos: array(TodoItem.t)) => {
    <Text>
      {React.string(
         "There are " ++ todos->Belt.Array.length->string_of_int ++ " To-Dos",
       )}
    </Text>;
  };
};

[@react.component]
let make = () => {
  let queryResult = TodosQuery.use();

  <View>
    {switch (queryResult) {
     | {loading: true, data: None} => <Text> "Loading"->React.string </Text>
     | {loading, data: Some({todos}), error} =>
       <View>
         <dialog>
           {loading ? <Text> "Refreshing..."->React.string </Text> : React.null}
           {switch (error) {
            | Some(_) =>
              <Text>
                "Something went wrong, data may be incomplete"->React.string
              </Text>
            | None => React.null
            }}
         </dialog>
         <TodoCount todos />
       </View>
     | {loading: false, data: None} =>
       <Text> "Error loading data"->React.string </Text>
     }}
  </View>;
};
