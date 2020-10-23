open ReactNative;
module QueryResult = ApolloClient.Types.QueryResult;

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
  let queryResult = TodosQuery.use();

  <View>
    {switch (queryResult) {
     | {loading: true, data: None} => <Text> "Loading"->React.string </Text>
     | {loading, data: Some({todos}), error, fetchMore} =>
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
         <View>
           <TouchableOpacity
             onPress={_ =>
               fetchMore(
                 ~updateQuery=
                   (previousData, {fetchMoreResult}) => {
                     switch (fetchMoreResult) {
                     | Some({todos: newTodos}) => {
                         todos:
                           Belt.Array.concat(previousData.todos, newTodos),
                       }
                     | None => previousData
                     }
                   },
                 (),
               )
               ->Js.Promise.then_(
                   result => {
                     switch (result) {
                     | Ok(_) => Js.log("fetchMore: success!")
                     | Error(_) => Js.log("fetchMore: failure!")
                     };
                     Js.Promise.resolve();
                   },
                   _,
                 )
               ->Utils.Promise.ignore
             }>
             <Text> "Fetch More!"->React.string </Text>
           </TouchableOpacity>
         </View>
       </View>
     | {loading: false, data: None} =>
       <Text> "Error loading data"->React.string </Text>
     }}
  </View>;
};
