# <span style="font-family:Magneto; font-size:1.5em;">fisk</span>

An ergonomic 54-key hand wired split keyboard running QMK on the Elite-C microcontroller, living inside its 3D-printed case.

![image info](./images/fisk1.png)

## Features
- split, Elite-C microcontroller, 54-keys, column stagger, ring finger and pinky splay, slightly tented case (2° toward user and 3° outward), support for one rotary endoder per half, one 128x32 OLED per half, hot-pluggable RJ10 connection between halfs and a transport case
## Acknowledgements
This keyboard draws inspiration from many sources and would not have been possible without the works of others.
Some that deserve to be mentioned above all else are:
- the famous Kyria by Thomas Baart, [[https://splitkb.com][splitkb.com]]

    The aggressive column stagger, the thumb cluster and the general shape are heavily influenced by the Kyria. The use and placement of a rotary encoder also comes from the various Kyria layouts floating around. Even the two extra index finger keys draw inspiration from here, as there was enough space in my 3D mock-up due to the different MCU placement and I just love dedicated keys for brackets.
    Would I not have gone down the route of designing my very own keyboard, the Kyria would have been one of the most tempting options of all the split keyboards I came across in my research.
    
- the Architeuthis dux by @tapioki

    Going one step beyond a mere column stagger and adding column splay immedietely made sense to me and seemed like the next logical step. The even more extreme pinky stagger was a welcome encouragement in the design process of the physical layout (apparently my pinkies are rather short) and the column splay turned out to feel very natural.
    
- [[https://www.thingiverse.com/thing:4768218][the Lotus58 case design]] by Matt James.

- QMK wizardry by (in alphabetical order): [[https://github.com/andrewjrae][@andrewjrae]], [[https://github.com/drashna][@drashna]], [[https://github.com/GauthamYerroju][@GauthamYerroju]],[[https://github.com/JReneHS][@JReneHS]], [[https://github.com/rafaelromao][@rafaelromao]]

Keyboard Maintainer: [[https://github.com/vvhg1][@vvhg1]]

## Keymap
![image info](./images/keymap.png)
This is my personal keymap, main features include: one rotary encoder, Colemak-dh and Qwerty (both have somewhat modified symbols), layers, custom leader key, custom layer logic, custom oneshot modifiers, end of sentence, case modes (CAPSWORD, x_case, NUMW0RD), power brackets and dynamic info on both OLED displays.

**Note:** This keymap assumes a US International ANSI layout and a Windows OS. This is due to my need for some international characters like £, Ä, Ö, Ü, ß. I have not tested it on other OS and shortcuts are the Win ones, but it should not be overly complicated to adapt.

### Leader Key
Custom leader key implementation, original author is [[https://github.com/andrewjrae][@andrewjrae]].
I made a few changes:
    - for one I changed the leader key to toggle, so it can be used to escape the leader sequence.
When activated, the leader key changes layers back to the default layer if it is not the highest layer.
I made a few changes to how the leader sequence is displayed on the oled. If the sequence gets too long, it starts scrolling with every new key press, only displaying the last n (of course this value can easily be changed) keys.
I also fiddled around with the logic in general to adapt it to my use case.
Probably the biggest aspect  is more a different approach of implementation/usage. For me the biggest limitation of the leader key was that the action was not easily repeatable, so I added open ended sequences. When a leader sequence is finished, the action is executed, as one would expect, but the leader sequence then keeps listening instead of terminating, so if the last key in the sequence is tapped again, the action is being repeated. This is done so long as no other key is pressed. If an other key gets pressed, the sequence is terminated and the key is processed as normally. For actions like next/previous or up/down actions, I let both corresponding keys through, e.g. if w were up and s down, pressing s after w would not disable the leader function and instead perform the down action.

### Custom Layer logic
This also works with NO_ACTION_TAPPING defined.
Layers toggle on tap and momentarily activate when held. Memory of previously active layer, returning to it, rather than to the base layer. <!--as an option?)-->

### Custom one shot modifiers
Light weight modifiers that work when NO_ACTION_TAPPING and NO_ACTION_ONESHOT are defined. They behave like normal modefiers when held, but when tapped they modify only the next key. The one shot function is disarmed when tapped again, or when tapped and then held behave like normal modifiers.
One shot is not disabled by: space, del, backspace and modifiers. That means that e.g. ctl + shift + "A" do not have to be chorded but can be hit in sequence.

### End Of Sentence
This makes the transition between sentences a little smoother. Instead of typing `.`-`SPACE`-`SHIFT`- typing -`..`- has the same effect. The idea is not mine, and it seems, I can't find the source. The implementation however is my work.
### Case Modes
Case modes are slightly adapted to account for NO_ACTION_TAPPING and NO_ACTION_ONESHOT and for my use case.
#### Caps Word
Description is largely the original by [[https://github.com/andrewjrae][@andrewjrae]].
Caps word is a feature [[https://github.com/andrewjrae][@andrewjrae]] came up with a while back that essentially acts as a caps lock key but only for the duration of a "word".
This makes macros like =CAPS_WORD= really easy to type, it feels a lot like using one shot shift, and it pairs very nicely with it.
What defines a "word" is sort of up for debate, he started out with a simple check to see if he had hit space or ESC but found that there were other things he wanted to exit on, like punctuation.
So now it detects whether `space`, `backspace`, `-`, `_`, or an alphanumeric is hit, if so we stay in caps word state, if not, it gets disabled. he also checks for mod chording with these keys and if you are chording, it will also disable caps word (e.g. on `Ctrl+S`).

The actual behavior of when to disable caps word can be tweaked using `terminate_case_mode()`.

`By default caps lock is used as the underlying capitalization method, however you can also choose to individually shift each keycode as the go out. This is useful for people who have changed the functionality of caps lock at the OS level. To do this simply add #define CAPSWORD_USE_SHIFT in you config.h.`

**Note:** I switched that around so that shift is now default, unless `#define CAPSWORD_USE_CAPS` is defined.

To use this feature `enable_caps_word()` or `toggle_caps_word()` can be called from a macro, combo, tap dance, or whatever else you can think of.

#### X Case
X-Case is an idea from [[https://github.com/baffalop][@baffalop]], it takes the idea of caps word but applies it to different kinds of programming cases.
So for example say you want to type `my_snake_case_variable`, rather than pressing `_` every time (which is almost certainly behind a layer), you can hit a "snake_case" macro that turns all your spaces into underscores, it can then be exited using whatever you define as the end of a word in `terminate_case_mode()`.
[[https://github.com/baffalop][@baffalop]] also suggested using a double tap space as an exit condition, which is also implemented here.

Now this is just a snake case macro, what if you want kebab-case? Well x-case can be applied here, but now instead of replacing space with an `_` it replaces it with a `-` instead.
The idea of x-case is to make it easy to achieve these kinds of case modes. For example to enable snake_case mode, you just need to call `enable_xcase_with(KC_UNDS)` and for kebab it's simply `enable_xcase_with(KC_MINS)`.

So you might ask, what about camelCase? Well, we got that covered too! If you call `enable_xcase_with(OSM(MOD_LSFT))`, your spaces will be turned into one shot shifts enabling you to write camelCase.

Finally, because you might want to use this for some more obscure use cases, there's the `enable_xcase()` function.
This function will intercept your next keystroke and use that as it's case delimiter.
For example, calling `enable_xcase()` and then hitting your `/` key will result in your spaces begin turned into slashes. (This is the equivalent of calling `enable_xcase_with(KC_SLSH))`)

To make this a little more flexible, you can define a default separator so that typing non-symbols defaults to that separator.
This default separator can be configured with the `DEFAULT_XCASE_SEPARATOR` macro, by default it is `KC_UNDS` for snake_case.
To enable this you need to specify what keys will enter default mode, this configured with the `use_default_xcase_separator()` function.

#### Num Word

NUMWORD is a similar concept by Joshua T. [[https://github.com/replicaJunction][@replicaJunction]]. I added NUMWORD to my Case Modes, which also means, that I changed the means of activation, as all Case Modes are activated by leader key sequences. This can be combined with X-Case. To use this feature `enable_num_word()` or `toggle_num_word()` can be called from a macro, combo, tap dance, or whatever else you can think of.

**Note:** The implementation of NUMWORD requires that the keyboard's layer definitions be accessible in a header file. In this case, the layer definitions are in enumlayers.h, so I make them accessible by adding `#include enumlayers.h` in casemodes.c.

### Power Brackets
These are bracket pairs of different types, single and quote pairs. They either produce an empty pair and place the cursor inside the brackets on a simple key press like `(I)`, `{I}`, `[I]`, or when modified with ALT they `(wrap) {the} [last] "word"`. Due to the ALT modifier, ESC is sent to neutralise the dead ALT keypress on the US Intl. layout.
### Other
I made the Grave key, which is a dead key in the US Intl. layout, active again as I don't need the dead key behaviour of it and I find it annoying. To revert to the standard behaviour, simply comment out this part in keymap.c:  
         
         case KC_GRAVE:  
            if (record->event.pressed) {  
                if (get_mods() & MOD_MASK_SHIFT) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_GRAVE) SS_TAP(X_SPC)));
                } else {
                    SEND_STRING(SS_TAP(X_GRAVE) SS_TAP(X_SPC));
                }
            }
            return false;

## OLEDs
I added some pretty graphics to make the info easily recognisable as this build only has a 128x32 display.


![image info](./images/oled_layers.png)  

![image info](./images/oled_mods.png)

The modifier key design originally comes from [[https://github.com/JReneHS][@JReneHS]], source: [https://github.com/JReneHS/crkb_conf](https://github.com/JReneHS/crkb_conf). I just enlarged the icons from 2 characters high to 3 characters while keeping the aspect ratio. As I find the COMMAND icon a lot prettier than the boring CONTROL icon, I decided to use it despit running Windows. I also took some inspiration for my layer indicator from him. If mirroring is on, instead of cramming yet another icon into my very limited OLED real estate, the whole screen is inverted.

### OLED info
Left-side OLED displays dynamic data:
- Base Layer
    - Colemak-dh
    - Qwerty
    
- Current Layer
    - Colemak-dh
    - Qwerty
    - Numbers
    - NAvigation
    - Functions
    - Aux
    
- Case Modes
    - C for CASEMODE
    - S for _snake_case_
    - N for Numw0rd
    - X for _CAPS_AND_SNAKE_CASE
    
Right-side OLED displays dynamic data:
- Current modifier status
- Current mode of rotary encoder
- Leader key sequence

### Cheap trick OLED
As I was pressed for space with console/debug enabled, I got rid of something rather unnecessary, instead of disabling core features of my keymap...
OLED will save some space at compile time by disabling most graphics. Information is still being displayed, just not in a pretty way. 

## Mirroring 
Is supported for one hand typing, can be disabled in rules.mk (SWAP_HANDS_ENABLE)

## Rotary Encoder

Press the encoder to cycle between:
- Word Nav (Ctrl + Left / Right)
- Left / Right
- Up / Down
- Page Up / Page Down
- Vscode Next / Previous Editor
- Vscode Next / Previous Tab



## Make
Make example for this keyboard (after setting up your build environment):

    make fisk:vvhg

Example of flashing this keyboard:

    make fisk:vvhg:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

A build guide for the fisk can be found at...
