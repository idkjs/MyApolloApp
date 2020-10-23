open ReactNative;
type reactNativeNewAppScreenColors = {
  .
  "primary": string,
  "white": string,
  "lighter": string,
  "light": string,
  "black": string,
  "dark": string,
};
[@bs.module "react-native/Libraries/NewAppScreen"]
external colors: reactNativeNewAppScreenColors = "Colors";
let styles =
  Style.(
    StyleSheet.create({
      "scrollView": style(~backgroundColor=colors##lighter, ()),
      "engine": style(~position=`absolute, ~right=0.->dp, ()),
      "body": style(~backgroundColor=colors##white, ()),
      "sectionContainer":
        style(~marginTop=32.->dp, ~paddingHorizontal=24.->dp, ()),
      "sectionTitle":
        style(~fontSize=24., ~fontWeight=`_600, ~color=colors##black, ()),
      "sectionDescription":
        style(
          ~marginTop=8.->dp,
          ~fontSize=18.,
          ~fontWeight=`_400,
          ~color=colors##dark,
          (),
        ),
      "highlight": style(~fontWeight=`_700, ()),
      "button": style(~width=dp(120.), ~height=dp(120.) ,~borderRadius=60. ,~justifyContent=`center ,~alignItems=`center, ()),
      "footer":
        style(
          ~color=colors##dark,
          ~fontSize=12.,
          ~fontWeight=`_600,
          ~padding=4.->dp,
          ~paddingRight=12.->dp,
          ~textAlign=`right,
          (),
        ),
    })
  );
module ApolloQueryResult = ApolloClient.Types.ApolloQueryResult;
module ObservableQuery = ApolloClient.Types.ObservableQuery;

module AddTodoMutation = [%graphql
  {|
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
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
        text
        completed
      }
    }
  |}
];

let logTodos = _ =>
  Client.instance.query(~query=(module TodosQuery), ())
  ->Utils.Promise.then_(result => {
      Js.Promise.resolve(
        switch (result) {
        | Ok({data: {todos}}) => Js.log2("query To-Dos: ", todos)
        | Error(error) => Js.log2("Error: ", error)
        },
      )
    })
  ->Utils.Promise.ignore;

let addTodo = _ =>
  Client.instance.mutate(
    ~mutation=(module AddTodoMutation),
    {text: "Another To-Do"},
  )
  ->Utils.Promise.then_(result =>
      Js.Promise.resolve(
        switch (result) {
        | Ok({data}) => Js.log2("mutate result: ", data)
        | Error(error) => Js.log2("Error: ", error)
        },
      )
    )
  ->Utils.Promise.ignore;

let observableQuery =
  Client.instance.watchQuery(~query=(module TodosQuery), ());

let watchQuerySubscription =
  observableQuery.subscribe(
    ~onNext=
      result =>
        switch (result) {
        | {data: Some({todos})} => Js.log2("watchQuery To-Dos: ", todos)
        | _ => ()
        },
    (),
  );
// Unsubscribe like so:
// watchQuerySubscription.unsubscribe();

[@react.component]
let make = () => {
  <View style={styles##sectionContainer}>
    <TouchableOpacity style={styles##button} onPress=logTodos>
      <Text style={styles##sectionDescription}> "Log To-Dos (Reason Promise)"->React.string </Text>
    </TouchableOpacity>
    <TouchableOpacity style={styles##button} onPress=addTodo>
      <Text style={styles##sectionDescription}> "Add To-Do"->React.string </Text>
    </TouchableOpacity>
    <Text style={styles##sectionDescription}>
      "[ To-Dos also logged in console with watchQuery ]"->React.string
    </Text>
  </View>;
};
