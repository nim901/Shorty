Shorty
==========

Master keyboard shortcuts

Changelog Ver 0.1:
* First version. It kinda works.

TODO and bugs:
* Support for shift key
* Support for keys that are using shift (semicolon,ampersand...)
* Support for multiple press on the same key
* Case sensitive support
* Memory leaks
* New gui
* Fixing more bugs.

Main Window
![Image of main window](http://i.imgur.com/aNmQ95d.png)

![Image of main window](http://i.imgur.com/vrspncm.png)

![Demo video](http://i.imgur.com/swurqxW.gif)

## How to create plugins:

Plugins are just a simple XML file with the application name, shortcut name and keys.
Each shortcut has it's id (starting from 0), it's name, and the keys that triggers it.
Modifiers keys that avilable are:
    Ctrl
    Alt
    Enter 
* Note: modifiers are case sensitive regular keys are not.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Paint>
    <Shortcut id="0">
        <Name>Copy</Name>
      <Key>Ctrl</Key>
      <Key>C</Key>
    </Shortcut>
    <Shortcut id="1">
        <Name>Paste</Name>
      <Key>Ctrl</Key>
      <Key>V</Key>
    </Shortcut>
</Paint>
```

Please note that this is my first QT C++ project so be nice to me :>
