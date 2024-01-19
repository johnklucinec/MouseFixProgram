<div align="center">

 <h1><a href="https://cplusplus.com/"><img src="https://img.shields.io/badge/C++-00599C.svg?style=for-the-badge&logo=C++&logoColor=white"></a> Mouse Optimization App <a href="https://www.qt.io/product/qt6"><img src="https://img.shields.io/badge/Qt-41CD52.svg?style=for-the-badge&logo=Qt&logoColor=white"></a></h1>
 <h4>Made with C++ and Qt 6 Widgets</h4>
</div>

## Preview

![Screenshot 2024-01-17 182245](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/095d464e-2410-4379-bf49-fe321193f224)

### Intro

When I first began to learn coding, I was not particularly fond of command-line programs. Although they can be useful tools for various applications, having a good GUI is always a plus. I personally love the Window's Acrylic look, and I was a bit frustrated to learn that Qt does not support this theme. Well, I had to work with what I had, and I made my own theme instead. 

What is the point of this program? 

I wanted to learn a popular GUI framework and practice using C++. I coded all the mouse tweaks and registry editing code myself.

**Sources**

[Registry Editor | Mouse Tweaks | MarkC Fix](https://github.com/johnklucinec/MouseFixApp)

[MarkC Mouse Fix](http://donewmouseaccel.blogspot.com/2010/03/markc-windows-7-mouse-acceleration-fix.html)

[Savitarax's YouTube](https://www.youtube.com/channel/UCp-bDh-KT2b3Xb8WViYoHMQ)
## Index

- [Features](#features)
- [Supported Tweaks](#supported-tweaks)
  - [Savitarax](#savitarax)
  - [MarkC](#markc)
- [Usage](#usage)
- [Examples](#examples)
  - [Reactive Buttons](#reactive-buttons)
  - [Custom Message Boxes](#custom-message-boxes)
  - [Moveable Windows](#moveable-frameless-window)
  - [Moveable Message Box](#moveable-message-box)
- [Future Versions/Features](#future-versionsfeatures)
- [Questions/Suggestions/Bug Reports](#questionssuggestionsbug-reports)

## Features
<div align="center">

**Matching Message Boxes**

  ![message_box](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/d6653a33-adee-4563-b099-dad1a09c6c05)
  
**Error Handling**

  ![error_handle](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/89c6514c-aaec-4c25-96b3-5573882df2b6)

</div>

## Supported Tweaks


>[!IMPORTANT]\
> After you apply the tweaks, make sure you restart your computer.

### Savitarax
The Savitarax tweaks are designed to improve the performance of your mouse inputs.

  * **Change Mouse Buffer Size:** This allows you to lower the mouse event buffer size to reduce input lag. By default, this value is set to 100. A value between 20 to 100 is recommended. If you have a high polling rate mouse, you can go under 20.
  * **Change CSRSS Priority:** CSRSS stands for Client Server Runtime Process. It's responsible for the user interface of Windows, including mouse input. Giving CSRSS higher priority can improve mouse responsiveness by giving it more CPU time.

  While I could explain what these tweaks do, I would recommend watching [this video](https://www.youtube.com/watch?v=kVHiSsZhR_c&t=47s) by Savitarax. He does and insane amount of research for each of his videos, so please check him out. 

### MarkC

The MarkC mouse fix resolves mouse acceleration issues in Windows, by modifying the system's mouse settings for better control over mouse movements. It's particularly useful for gamers.

* Redefines the mouse curve when 'Enhance pointer precision' is applied, resulting in a 1-to-1 relationship between mouse and pointer movement.
* For the best mouse response, set the Control Panel pointer speed slider to the middle position (6th).

How do you know what value to use?
  * Find the display DPI that you currently use: 
  * Click Start, click Control Panel, select Appearance and Personalization, select Display.
    * See if you have ``100%`` or ``125%`` or ``150%`` selected. 
  * Select the option in the drop down menu that matches the DPI%


## Usage

### Common Error Codes

**Error Code: 2**

Error code 2 usually signifies ``ERROR_FILE_NOT_FOUND``. Pressing "Set Default" under the *Savitarax Fix* tab deletes the registry values associated with the tweak. If you press it more then once, it is trying to delete a file which doesn't exist.

**Error Code: 5**

Error code 5 typically signifies ``ERROR_ACCESS_DENIED``. This means the program does not have sufficient permissions to edit the registry. Please ensure that you run the program as an administrator or check if an antivirus is blocking it.

> [!WARNING]\
> These tweaks modify registry values. I ensured the implementation is safe, but if you modify the code, make sure you know what you're doing.

## Examples

### Reactive Buttons
Reactive buttons! Yeah I know, this is just basic qss (Qt's version of css)
![reactive](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/3982aac3-85b6-447f-878a-23736480a5ef)

### Custom Message Boxes
The default message box looked weird, so I had to make my own. 
![message_boxes](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/94f8cfc4-e178-406e-8a93-8b59f50dd09d)

### Moveable Frameless Window
This was more challenging than I anticipated. Plus, making sure that the buttons didn't cause any glitches was even more difficult.
![moving_widget](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/241169dc-25d8-4b64-9b36-7b0609115452)

### Moveable Message Box
More spinning :)
![move_message](https://github.com/johnklucinec/MouseFixProgram/assets/72411904/30ff8ab1-8376-4814-83a2-d92ffeacd67f)

## Future Versions/Features
No plans for now. I might come back to this project and make a full Window's Optimization program. I did this once before, but I want to make one that is actually good. 

## Questions/Suggestions/Bug Reports
For questions, suggestions, or to report bugs, please contact me on Discord at DaddyJuanito or open an issue on the GitHub repository.
