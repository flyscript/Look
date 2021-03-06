# Look - A Tizen Watch Project

![image](https://user-images.githubusercontent.com/39959063/167960394-97bb13ba-ae4e-4abc-ad6a-d922f0dbbfe0.png)

This watchface was designed because I was frustrated with a lack of aviation instrument-inspired designs on the Samsung Galaxy watch store, and I wanted to learn how to make my own.

This project has actually been a great way to brush back up on my C/C++ skills after spending so long using primarily C# in my work!

### Contents
- [Features](https://github.com/flyscript/Look#features)
- [Main Watchface](https://github.com/flyscript/Look#main-watchface)
- [Ambient Mode](https://github.com/flyscript/Look#ambient-mode)
- [Low Battery](https://github.com/flyscript/Look#low-battery)
- [Ambient Hand Overlap](https://github.com/flyscript/Look#ambient-hand-overlap)
- [Smooth Hand Animation](https://github.com/flyscript/Look#smooth-hand-animation)

## Features
![Main](https://user-images.githubusercontent.com/39959063/155225316-8fc0301a-a282-4879-89d3-1120acb93976.png)
- Second, Minute, and Hour hands (of course)
- Smoothly animated second and minute hand, that behaves akin to a real altimeter
- Shadows under each hand; adds depth, dimension, and brings the watchface into the real world
- Date/Day readout, styled to look like an altimeter setting window
- Battery level indicator, styled after fuel and volt gauges
- Ambient mode, styled after green glow-in-the dark cockpit instruments
- Low power mode, with reduced display output and styled after red glow-in-the dark cockpit instruments
- Modelled after real-world aviation cockpit instrumentation for an unparalleled aesthetic

## Main Watchface
![Main](https://user-images.githubusercontent.com/39959063/155225316-8fc0301a-a282-4879-89d3-1120acb93976.png)
![Main_Lowbat](https://user-images.githubusercontent.com/39959063/155229907-bf52daff-215f-45e5-8276-95c2a2e4ea70.png)

The watchface of course features hands for the current hour, minute, and second (which is animated smoothly like a real cockpit instrument would behave). Also featured is a day/date readout on the righthand side, similar to an [altimeter setting window](http://learntoflyblog.com/2015/04/16/cfi-brief-pitot-static-systems-and-flight-instruments-part-ii/) for pressure; and a battery indicator on the lower left-hand side.

The designs started from research into instruments in the Spitfire specifically, and I learned that there was actually a variety of instrument upgrades through the years as different models of Spitfire were produced. As I quickly learned from looking into these peices of equipment, historical aviation instrumentation as a hobby is a deep, deep rabbit hole!

The main face was inspired by the Altimeter (which tells you your altitude), which is an instrument that has evolved a lot over time in terms of looks. The altimeter that I specifically drew inspiration from was the one in the [Spitfire Mk XIV](https://en.wikipedia.org/wiki/Supermarine_Spitfire_(Griffon-powered_variants)#Mk_XIV_(type_379)), which entered service at the end of 1943 and saw use intercepting V1 flying bombs. The main components of this altimeter design are [still used](https://sarasotaavionics.com/avionics/5934pm3a-unlighted) very commonly [today](https://www.chiefaircraft.com/utd-5934p3.html).

The battery indicator on the watch is inspired from the graduated lines of Volt-meters (telling you the charge of the Spitfire's battery) and [some fuel gauges](http://spitfirespares.co.uk/Instruments%20fuel%20gauges%208.html), used by other aircraft of the period as well such as the Blenheim bomber.

Taking this historic equipment that helped win WW2, I made some modifications to make those elements better suited to a small, slightly more modern watchface; being careful to preserve the character of the original design elements.

## Ambient Mode
![Ambient](https://user-images.githubusercontent.com/39959063/155225518-8d5e95fe-07b9-44d7-b172-9b438b2db120.png)

I decided to model the "screensaver" ambient mode for this watch on the green "glow-in-the-dark" effect that some aviation instrumentation has. For the Spitfire, this was acheived by coating elements of the instruments in a radioactive Radium paint, and many instruments used today still actually contain this paint! Thankfully, the watch only needs regular pixels. The second hand is removed in this state, as updates occur only every minute in ambient mode, and the less pixels that are on (and the less thigns moving etc), the less battery drain.

## Low Battery
![Main_Lowbat](https://user-images.githubusercontent.com/39959063/155230026-3aa25a18-a495-431d-89f2-8099fbabd336.png)
![Ambient_Lowbat](https://user-images.githubusercontent.com/39959063/155230041-9623a581-5089-463e-9dfe-4250cba8708d.png)

Radium "glow-in-the-dark" paint doesn't only come in green, it can be red too! When the device has low battery, this is indicated by the battery watch hand becoming red, as if giving off some of this radioactive illumination. If in ambient mode, the watchface and hands of the watch become red instead of green, and the day/date functionality as well as some trimmings are removed for additional power saving.

## Ambient Hand Overlap
![Ambient_Overlap](https://user-images.githubusercontent.com/39959063/155229419-2bdf200d-0f78-4646-bfab-8f3d0b7d0dd6.png)
![Ambient_Lowbat_Overlap](https://user-images.githubusercontent.com/39959063/155230181-38fe7181-c1cf-4c71-ae9a-56642f180a92.png)

Earlier on I noticed that when the minute and hour hand are close to eachother, they formed an indistinct green (or red, if on low battery) blob that was difficult to differentiate. To make reading the watchface whilst it's ambient more intuitive, I added black borders around each hand so that they are more distinguished.

### Smooth Hand Animation
https://user-images.githubusercontent.com/39959063/155424982-31b11dd6-2a5a-4df1-bd7a-0fdb17519ee6.mp4

The second hand is animated using Edje, in 15-second increments because things get a bit loopy and glitchy if you attempt to do the 360 degree rotation in a single 60 second program. These 4 15-second programs cycle perfectly, with no noticeable effects when transitioning from one to the other, giving the effect of a completely smooth and uninterrupted rotation. The minute hand moves so short a distance over so long a time that it doesn't require such animation, and instead its angle is updated almost imperceptably each second with the tick, rather than wasting memory and battery on a whole animation cycle.

Edje is also used to create the date/day layout module on the righthand side, as a seperate element from the main background. This would be a prime target for future aniamtion work, e.g: getting it to wiggle when you tap on it, as if you were tapping on a real gauge.
