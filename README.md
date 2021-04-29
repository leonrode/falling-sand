<h1> SFML Falling Sand </h1>

<p>
A simulation of sand falling, written in C++ with the SFML Graphics library.
</p>

<h2>Introduction</h2>
<p>
This program creates a grid of squares, whose state can either be on or off, representing the presence or absence of sand in that given square. Each iteration, each square performs a check on the presence of squares in its vicinity, deciding where to move in the next iteration. These decisions are based on certain rules.
</p>

<h3>Demo</h3>

![](falling-sand.gif)
<h3>Rules</h3>
<p>
Each sand particle decides where to move based on these set of rules, tested each frame and in this particular order.  <i>The reason for this order is to try to prevent bias beacuse as soon as one test passes, the sand particle will not check the others.</i>
</p>
<ol>
<li> If the square directly beneath the sand particle is vacant, occupy it next frame.</li>
<li> If the squares below and to the left, and below and to the right are vacant, randomly choose which of those squares to occupy, and occupy it next frame.</li>
<li> If the square below and to the left is vacant, occupy it next frame.</li>
<li>  If the square below and to the right is vacant, occupy it next frame.</li>
</ol>

<h2>Installation</h2>
<p>
There is no binary to install, so just set up your SFML workspace as usual and copy the code in the <code>main.cpp</code> file.
</p>

<h2>License</h2>
<p>
This software is released under the <a href="https://www.gnu.org/licenses/gpl-3.0.en.html">GNU GPL v3 License</a>.</p>
<h2>Contact</h2>
<p>
If you have any questions or comments, please reach out to me <a href="mailto:leon.rode13@gmail.com">here</a>.
