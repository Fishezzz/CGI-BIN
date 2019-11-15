#!/bin/bash
echo -e "Content-type: text/html\n\n"
echo '<ul>
    <li><a href="./test.cgi">test.cgi</a></li>

    <li><a href="./ENV-CGI/env-cgi.cgi">ENV-CGI/env-cgi.cgi</a></li>
    
    <li><a href="./test/collect.cgi">test/collect.cgi</a></li>
    <li><a href="./test/hello-world.cgi">test/hello-world.cgi</a></li>
    <li><a href="./test/text.cgi">test/text.cgi</a></li>
    <li><a href="./test/viewdata.cgi">test/viewdata.cgi</a></li>

    <li><a href="./opdracht/index.html">opdracht/index.html</a></li>
    <li><a href="./opdracht/opdracht.cgi">opdracht/opdracht.cgi</a></li>
</ul>'
