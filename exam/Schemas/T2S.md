```mermaid
classDiagram
direction TB

    class Text2SpeachTextInputView {

    }

    class VoiceType {
        <<enum>>
    }

    Text2SpeachTextInputView ..> Text2SpeachSerivce: use

    class Text2SpeachSerivce {
        Convert(VoiceType type, string text)
    }

    Text2SpeachSerivce o--> Text2SpeachConverterFactory

    class Text2SpeachConverterFactory {
        Create(VoiceType type) Text2SpeachConverter
    }

    Text2SpeachConverterFactory ..> VoiceType
    Text2SpeachConverterFactory ..> Text2SpeachConverter: create

    class GoogleText2SpeachConverterAdapter {
        +Convert(VoiceType type, string text)
    }

    class AmazonText2SpeachConverterAdapter {
        +Convert(VoiceType type, string text)
    }

    class GoogleText2SpaechAPIClient {
    }

    class AmazonText2SpeachAPIClient {
    }

    class Text2SpeachConverter {
        +Convert(VoiceType type, string text)
    }

  <<interface>> Text2SpeachConverter

    GoogleText2SpeachConverterAdapter ..|> Text2SpeachConverter
    AmazonText2SpeachConverterAdapter ..|> Text2SpeachConverter
    GoogleText2SpeachConverterAdapter o--> GoogleText2SpaechAPIClient
    AmazonText2SpeachConverterAdapter o--> AmazonText2SpeachAPIClient

```