# MMCAccountSettingsSwitcher

A small tool for [MultiMC](https://multimc.org/) that manages minecraft settings (key bindings etc, everything stored in options.txt) for multiple users.

## Installation & Usage

No fancy installer, just copy the binary to whereever you want it (hint: the MultiMC folder is a good place, since you won't need to specify a path).

After that, open the MultiMC settings, custom commands tab. 
Pre-launch command | /path/to/your/MMCAccountSettingsSwitcher start
Post-exit command  | /path/to/your/MMCAccountSettingsSwitcher stop

It you put the binary in the MultiMC folder, you don'T have to specify a path, the binary name is sufficient.

## Compilation

### gcc
Open a console in the project folder and type
`> make`

### Visual Studio 2015+
Open the attached MMCAccoutSettingsSwitcher.sln and compile.
Versions after 2015 might require that you convert/upgrade the project/solution files, and older versions might not work at all. 

### other
For other compilers/platforms use your ingenuity but be careful for hygenic reasons. 
(this is just one source file and the json header, shouldn't be too difficult to figure out)

## Tested platforms

Windows 7 64bit (should run on other Windows versions as well)
Ubuntu 18.04 64 bit (should run on other linux systems as well)

## Notes

This uses [json from nlohmann](https://github.com/nlohmann/json), version 3.5.0 (included in the source, with a minor change to prevent a gcc warning).

## Licence

This is released unter the [MIT license](https://opensource.org/licenses/MIT).
