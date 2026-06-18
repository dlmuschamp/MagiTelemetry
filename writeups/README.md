# MagiTelemetry

This is the repo for my Magi-inspired telemetry daemon for Arch Linux. This is my first project written in **C**. 

The goal is that the project will display live hardware usage stats that mimic the Neon Genesis Evangelion's UI design while taking as little computational resources as possible. This is not to say this is the best way possible or most efficent approach. There are multiple things that I am choosing to build from scratch instead of using the already avaible tools just so I can get more practice personally with C and other programming things. 

A lot of this could probably be done pretty easily with just bash scripting. For example, all of batteryTelemetry.C can be replaced by a simple bash script looping acpi -b and catting that into a text file. I'm choosing to do this the long way in C.

**Ideas**
+ Have the laptop battery remaining match the 7-segment display countdown.
+ Have some type of bluetooth connectivity strength or wifi strength match the "psychographic display" and intentionally amp up the noise to make it seem more unstable than it is.

**References**
+ https://astromono.wordpress.com/2015/06/04/ui-design-of-evangelion/
+ https://zemnmez.medium.com/why-we-dont-have-uis-like-the-ones-in-neon-genesis-9b6631dc3714
+ https://www.pedrofleming.com/neongenesisevangelion
