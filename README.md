mdBrowser
=========

This program displays the system file tree in the left pane, and a webview in the right pane. When a Markdown file (*.MD) is selected, the program runs it through pandoc and converts it to an HTML file in your tmp path, then loads the file into the webview. The tmp file is deleted after it is loaded.

pandoc was selected because it is fast and produces quality renders.

Screenshot
----------

![Alt text](https://github.com/arduent/mdBrowser/blob/current/Screenshot.png?raw=true "Screenshot of mdBrowser")

Caveats
-------

Links in the MD files do not work at the moment. 

Build
-----

```
qmake
make
```

Install
-------
```
sudo make install
```

This will put the executable in 
/opt/mdBrowser/bin/mdBrowser.

Install 'pandoc' on your system.

FreeBSD:
```
pkg install hs-pandoc
```

Fedora:
```
sudo dnf install pandoc
```

Debian:
```
sudo apt install pandoc
```

Add /opt/mdBrowser/bin to your path, then you can call 'mdBrowser' from any path on your system.
Alternatively, cd to your desired path and run /opt/mdBrowser/bin/mdBrowser.

Uninstall
---------
```
sudo make uninstall
```

Clean
-----
```
make clean
```
Also, you may restore to pristine using:
```
make distclean
```






