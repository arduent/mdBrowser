mdBrowser
=========

This program displays the system file tree in the left pane, and a webview in the right pane. When a Markdown file (*.MD) is selected, the program runs it through pandoc and converts it to an HTML file in your tmp path, then loads the file into the webview. The tmp file is deleted after it is loaded.

pandoc was selected because it is fast and produces quality renders.

Caveats
-------

Links in the MD files do not work at the moment. 


