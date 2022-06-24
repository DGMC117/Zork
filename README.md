# Introduction
Hi! This is Blue Mesa, a text game that plays on a computer console and has no graphics!

This game has been implemented as part of the application for the "Advanced Programming for AAA Video Games" master's degree offered by UPC Talents School.

Author: David Garcia De Mercado

# Information

You can find the source code for the game following this link: https://github.com/DGMC117/Zork

# Walkthrough

1. The machine in the recovery room allows you to heal yourself whenever your life points are low. You should take the glowdust and the dagger, and also equip the dagger. Then head east.

```
take glowdust
take dagger
equip dagger
e
```

2. You can talk with the professor, who will give you more details about what is happenning. If you look at the poster, you will find a clue on how to brew a strength potion that will be useful later. The card object is just an easter egg. After this, head east.

```
talk professor
look poster
e
```

3. Take the vibranium inside the box. With this we can build a powerful shield later. Wait to kill the spawn, we can become stronger before to secure the kill. Go east.

```
take vibranium in box
e
```

4. Take the biochip. We will use this to create the mythocube later. Also take the candybar and use it. If you look at your stats before and after, you will se the increase in health that using this item gives you. After this, you will see that the exit to the south is locked. This is the time to go back and kill the spawn.

```
take biochip
take candybar
use candybar
w
```

5. Attach the spawn and hope for the best... Well, this is actually not a difficult fight. After it drops dead, loot the boody and take a look at the note it had with it. This note reveals the code to unlock the stairway up. Unlock the exit and go up.

```
attack spawn
loot spawn
look note
unlock up with code
0451
u
```

6. First of all, look at the computer. This will tell you the code that unlocks the reactor room. You can't take the frame yet because it is protected by an energy stream. What you can do is fabricate a shield with the forge using the vibranium we took earlier. Equip it. After this go back to the engineering room.

```
look computer
transform vibranium using forge
take shield from forge
equip shield
d
e
```

7. Unlock the reactor room with the code 2222 and enter it. Take the battery and the bottle, and break the cable with the dagger or the claws. This will allow you to pick up the frame from the assembly room. Then go to the assembly room.

```
unlock south with code
2222
s
take battery
take bottle
break cable with dagger
n
w
u
```

8. Take the frame and combine it with the biochip using the assembler to fabricate a mythocube. Take the mythocube and head to the laboratory.

```
take frame
combine frame with biochip using assembler
take mythocube from assembler
d
w
```

9. If you want to defeat in battle Animar, just for fun (the game can be beaten without this), you will want to create the strength potion using the burner. Thiis will require the bottle and the glowdust. you also might want to heal at the recovery machine. Use the battery to unlock the north exit, and then go north. Keep in mind that beating Animar will require a bit of luck. Use the mythocube on Animar to beat the game.

```
combine bottle with glowdust using burner
take potion from burner
use potion
w
use machine
e
unlock north with battery
n
use mythocube on animar
```

# Have Fun!

I have scattered some easter eggs and references. Can you catch them all?

# License
MIT License

Copyright © 2022 David Garcia De Mercado

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.