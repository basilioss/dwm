# dwm

## Patches

- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/): toggle fullscreen for a window
- [alttagsdecoration](https://dwm.suckless.org/patches/alttagsdecoration/): alternative text for tags which contain at least one window.
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/): center all floating windows
- [alwaysontop](https://dwm.suckless.org/patches/alwaysontop/): set one floating window to be always-on-top 
- [autostart](https://dwm.suckless.org/patches/autostart/)
- [moveresize](https://dwm.suckless.org/patches/moveresize/): move and resize dwm's floating windows using keyboard bindings
- [noborder](https://dwm.suckless.org/patches/noborder/): remove the border when there is only one window visible
- [notitle](https://dwm.suckless.org/patches/notitle/): remove the title from the bar
- [pertag](https://dwm.suckless.org/patches/pertag/): keeps layout, mwfact, barpos and nmaster per tag
- [scratchpad](https://dwm.suckless.org/patches/scratchpad/)
- [shiftview](https://dwm.suckless.org/patches/nextprev/): cycle through tags
- [swallow](https://dwm.suckless.org/patches/swallow/): this patch helps users spawning a lot of graphical programs from their command line by avoiding cluttering the screen with many unusable terminals
- [systray](https://dwm.suckless.org/patches/systray/)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/): gaps + tile, bstack, bstackhoriz, centeredmaster, centeredfloatingmaster, deck, fibonacci (dwindle, spiral), grid and nrowgrid layouts.  By default some of them are disabled

## Keybindings

All the keybindings are located in the `config.def.h`. By default `MODKEY` is `super` or `windows` key.

## Installation

```bash
git clone https://github.com/basilioss/dwm
cd dwm
sudo make install
```

If you've never compiled dwm before, have a look at this guide: https://github.com/sineemore/suckless-101
