open ReactNative;
module Cache = ApolloClient.Cache;

module AddTodoMutation = [%graphql
  {|
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        completed
        text
      }
    }
  |}
];

module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        id
        completed
        text
      }
    }
  |}
];

[@react.component]
let make = () => {
  let (mutate, result) = AddTodoMutation.use();

  switch (result) {
  | {called: false} =>
    <View>
      <Text> "Not called... "->React.string </Text>
      <TouchableOpacity
        onPress={_ => mutate({text: "Another To-Do"})->ignore}>
        <Text> "Add To-Do"->React.string </Text>
      </TouchableOpacity>
      <Text> " "->React.string </Text>
      <TouchableOpacity
        onPress={_ =>
          mutate(
            ~optimisticResponse=
              _variables =>
                {
                  todo: {
                    __typename: "TodoItem",
                    id: "optimisticResponseTodo",
                    completed: None,
                    text: "To-Do from optimisticRespomse",
                  },
                },
            ~update=
              ({writeFragment, writeQuery}, {data}) =>
                switch (data) {
                | Some({todo}) =>
                  /**
                   * Apollo docs use cache.modify, but it's not typesafe. I recommend some
                   * combination of readQuery / writeQuery / writeFragment
                   */
                  Js.log2("mutate.update To-Do: ", todo);
                  let _unusedRef =
                    writeFragment(
                      ~fragment=(module Fragments.TodoItem),
                      ~data={
                        __typename: todo.__typename,
                        id: "fragmentToDo",
                        completed: None,
                        text: "To-Do from writeFragment",
                      },
                      (),
                    );
                  let _unusedRef =
                    writeQuery(
                      ~query=(module TodosQuery),
                      ~data={
                        todos: [|
                          {
                            __typename: todo.__typename,
                            id: "writeQueryToDo",
                            completed: None,
                            text: "To-Do from writeQuery",
                          },
                        |],
                      },
                      (),
                    );
                  ();
                | None => ()
                },
            ~refetchQueries=[|
              TodosQuery.refetchQueryDescription(),
              // - OR -
              String("TodosQuery") // Should rarely be needed?
            |],
            {text: "Another To-Do"},
          )
          ->ignore
        }>
        <Text> "Add To-Do (all the bells and whistles)"->React.string </Text>
      </TouchableOpacity>
    </View>
  | {loading: true} => <Text> "Loading..."->React.string </Text>
  | {data: Some({todo: {text}}), error: None} =>
    <Text> {React.string("To-Do added: \"" ++ text ++ "\"")} </Text>
  | {error} =>
    <View>
      <View>
        <Text> "Error loading data"->React.string </Text>
        {switch (error) {
         | Some(error) =>
           <Text> {React.string(": " ++ error.message)} </Text>
         | None => React.null
         }}
      </View>
    </View>
  };
};
