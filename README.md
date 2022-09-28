# dwm

![dwm](https://user-images.githubusercontent.com/71596800/192819493-d050a256-f8f2-48ff-99c9-59159b632d50.png)

## Patches

- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/): center all floating windows
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [monoclesymbol](https://dwm.suckless.org/patches/monoclesymbol/): hide the number of open clients in the current tag in monocle layout
- [noborder](https://dwm.suckless.org/patches/noborder/): remove the border when there is only one window visible
- [pertag](https://dwm.suckless.org/patches/pertag/): keeps layout, mwfact, barpos and nmaster per tag
- [scratchpad](https://dwm.suckless.org/patches/scratchpad/)
- [swallow](https://dwm.suckless.org/patches/swallow/): this patch helps users spawning a lot of graphical programs from their command line by avoiding cluttering the screen with many unusable terminals
- [systray](https://dwm.suckless.org/patches/systray/)
- [tab](https://dwm.suckless.org/patches/tab/): transforms the monocle layout into a ''tabbed'' layout if more than one window is present on the monocle view
- [truecenteredtitle](https://dwm.suckless.org/patches/truecenteredtitle/): center window title
- [underlinetags](https://dwm.suckless.org/patches/underlinetags/)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/): gaps + tile, bstack, bstackhoriz, centeredmaster, centeredfloatingmaster, deck, fibonacci (dwindle, spiral), grid and nrowgrid layouts.  By default some of them are disabled
- [shiftview](https://dwm.suckless.org/patches/nextprev/): cycle through tags
- [resizecorners](https://dwm.suckless.org/patches/resizecorners/): resize windows from each corner

## Requirements

- [slstatus](https://github.com/basilioss/slstatus) for status bar (optional)
- If dwm crash on startup, try to install `libxft-bgra` to properly render emoji in the status/info bar

## Keybindings

All the keybindings are located in the `config.def.h`. By default `MODKEY` is `super` or `windows` key.

## Installation

```bash
git clone https://github.com/basilioss/dwm
cd dwm
sudo make install
```

## Recompile

You need to recompile dwm after every change you make to its source code

```bash
cd dwm
rm -f config.h
sudo make install
```

