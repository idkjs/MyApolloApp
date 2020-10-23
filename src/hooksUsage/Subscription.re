open ReactNative;
module SorryItsNotASubscriptionForTodos = [%graphql
  {|
    subscription SorryItsNotASubscriptionForTodos {
      siteStatisticsUpdated {
        currentVisitorsOnline
      }
    }
  |}
];

[@react.component]
let make = () => {
  <View>
    <Text>
      "[ Not functional, but the examples are still valid ]"->React.string
    </Text>
    {switch (SorryItsNotASubscriptionForTodos.use()) {
     | {data: Some({siteStatisticsUpdated: Some({currentVisitorsOnline})})} =>
       <Text>
         {React.string(
            "There are "
            ++ string_of_int(currentVisitorsOnline)
            ++ " visitors online",
          )}
       </Text>
     | _ignoredForExample => React.null
     }}
  </View>;
};
