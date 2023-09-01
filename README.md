# Dot Matrix

A C++ Nintendo Game Boy emulator. Rendering is done via the SDL2 library. This was written for learning more about emulators. The CPU is quite accurate, passing blargs CPU instruction tests (except for 2 since a timer has not been implemented... and 1 as well since DAA broke again somehow 🙃). The PPU currently only renders background tiles currently and input doesn't work. 

## Screenshots

<img src="https://github.com/aminoa/dot-matrix/blob/main/screenshots/Tetris%20Title.png?raw=true" width="200"> <img src="https://github.com/aminoa/dot-matrix/blob/main/screenshots/Dr.%20Mario%20Title.png?raw=true" width="200"> 

## Thoughts 🤔

- Improving and testing the CPU early on is a good idea - using [Game Boy Doctor](https://robertheaton.com/gameboy-doctor/) (except for blarg's second test) helps a lot.
- Separating the Game Boy PPU and the SDL rendering is a good idea; it makes it much simpler to change SDL rendering methods and also to primarily focus on just writing to a "framebuffer" when dealing with the PPU, abstracting the rendering parts away
- When doing intermediate argument reads with the CPU, it's best to do the reads first with the MMU and store them into separate variables, then modify the PC at the very end of the switch statement (by adding to it from an array of byte counts); the code will be much easier to manage this way
- SDL_RenderDrawPoint is extremely slow, don't use it - I switched to using an SDL Surface but an SDL Texture would be even better
- I shamelessly stole from emulator source codes including [gbemu](https://github.com/jgilchrist/gbemu/), [PatBoy](https://github.com/Jonazan2/PatBoy/), [RosettaBoy](https://github.com/shish/rosettaboy/), [SameBoy](https://github.com/LIJI32/SameBoy/tree/master/), etc.
- I also used a lot of resouces online for study - these include the [pandocs](https://gbdev.io/pandocs/), [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) and some blog entries including [Robert's A Journey into GameBoy emulation](https://robertovaccari.com/blog/2020_09_26_gameboy/) and [Cinoop's Writing a Game Boy Emulator](https://cturt.github.io/cinoop.html).
- Missing features: Timers, MBCs, PPU window/sprite rendering, proper input support, audio

## Dependencies

I used vcpkg but this project should work with an alternate package manager/linking the external libraries directly.

```
SDL2
fmt
```
