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
  let (executeQuery, queryResult) = TodosQuery.useLazy();
  <View>
    {switch (queryResult) {
     | Unexecuted(_) =>
       <View>
         <Text> "Waiting to be executed... "->React.string </Text>
         <TouchableOpacity onPress={_ => executeQuery()}>
           //  <TouchableOpacity onPress={_ => executeQuery()} value="execute">
            <Text> "Execute"->React.string </Text> </TouchableOpacity>
       </View>
     | Executed({loading: true, data: None}) =>
       <Text> "Loading"->React.string </Text>
     | Executed({loading, data: Some({todos}), error}) =>
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
         <Text>
           {React.string(
              "There are "
              ++ todos->Belt.Array.length->string_of_int
              ++ " To-Dos",
            )}
         </Text>
       </View>
     | Executed({loading: false, data: None}) =>
       <Text> "Error loading data"->React.string </Text>
     }}
  </View>;
};
