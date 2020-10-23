/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * Converted from https://github.com/facebook/react-native/blob/724fe11472cb874ce89657b2c3e7842feff04205/template/App.js
 * With a few tweaks
 */
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

[@bs.module "react-native/Libraries/Core/Devtools/openURLInBrowser"]
external openURLInBrowser: string => unit = "default";

module Header = {
  [@react.component] [@bs.module "react-native/Libraries/NewAppScreen"]
  external make: _ => React.element = "Header";
};
module ReloadInstructions = {
  [@react.component] [@bs.module "react-native/Libraries/NewAppScreen"]
  external make: _ => React.element = "ReloadInstructions";
};
module LearnMoreLinks = {
  [@react.component] [@bs.module "react-native/Libraries/NewAppScreen"]
  external make: _ => React.element = "LearnMoreLinks";
};
module DebugInstructions = {
  [@react.component] [@bs.module "react-native/Libraries/NewAppScreen"]
  external make: _ => React.element = "DebugInstructions";
};

/*
 Here is StyleSheet that is using Style module to define styles for your components
 The main different with JavaScript components you may encounter in React Native
 is the fact that they **must** be defined before being referenced
 (so before actual component definitions)
 More at https://reason-react-native.github.io/en/docs/apis/Style/
 */
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

[@react.component]
let app = () =>
  <View>
    <ApolloClient.React.ApolloProvider client=Client.instance>
      <StatusBar barStyle=`darkContent />
      <SafeAreaView>
        <ScrollView
          contentInsetAdjustmentBehavior=`automatic style={styles##scrollView}>
          {Global.hermesInternal->Belt.Option.isNone
             ? React.null
             : <View style=styles##engine>
                 <Text style=styles##footer>
                   "Engine: Hermes"->React.string
                 </Text>
               </View>}
          <Header />
          <View style={styles##body}>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Fetching Data with Hooks"->React.string
              </Text>
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Simple Query"->React.string
              </Text>
              <Query_OverlySimple />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Typical Query"->React.string
              </Text>
              <Text> "TODO: Query_Typical"->React.string </Text>
            </View>
            // <Query_Typical />
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Lazy Query"->React.string
              </Text>
              <Text> "TODO: Query_Lazy"->React.string </Text>
            </View>
            // <Query_Lazy />
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Mutation"->React.string
              </Text>
              <Mutation />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Subcription"->React.string
              </Text>
              <Subscription />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Query with Subscription for More"->React.string
              </Text>
              <Query_SubscribeToMore />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Fetching Data Directly with the Client"->React.string
              </Text>
              <ClientBasics />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Fragments"->React.string
              </Text>
              <Text> "TODO: Query_Fragments"->React.string </Text>
            </View>
            // <Query_Fragments />
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "ClientBasics"->React.string
              </Text>
              <ClientBasics />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "See Your Changes"->React.string
              </Text>
              <ReloadInstructions />
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}> "Debug"->React.string </Text>
              <Text style={styles##sectionDescription}>
                <DebugInstructions />
              </Text>
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionTitle}>
                "Learn More"->React.string
              </Text>
              <Text style={styles##sectionDescription}>
                "Read the docs to discover what to do next:"->React.string
              </Text>
            </View>
            <View style={styles##sectionContainer}>
              <Text style={styles##sectionDescription}>
                <Text style={styles##highlight}>
                  "Reason React Native"->React.string
                </Text>
              </Text>
              <TouchableOpacity
                onPress={_ =>
                  openURLInBrowser(
                    "https://reason-react-native.github.io/en/docs/",
                  )
                }>
                <Text
                  style=Style.(
                    style(
                      ~marginTop=8.->dp,
                      ~fontSize=18.,
                      ~fontWeight=`_400,
                      ~color=colors##primary,
                      (),
                    )
                  )>
                  "https://reason-react-native.github.io/"->React.string
                </Text>
              </TouchableOpacity>
            </View>
          </View>
        </ScrollView>
      </SafeAreaView>
    </ApolloClient.React.ApolloProvider>
  </View>;
