<h1 align="center">
    🥚 Easter Hunt 🐰
</h1>

<div align="center">

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) 
[![Itch.io](https://img.shields.io/badge/Itch-%23FF0B34.svg?style=for-the-badge&logo=Itch.io&logoColor=white)](https://itsyakub.itch.io/easter-hunt) 
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white) 
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) 
[![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/yakub) 

</div>

<p align="center">
<strong>🐣 Easter Hunt</strong> is a small 2D game created with <a href="https://github.com/RobLoach/raylib-cpp">RobLoach/raylib-cpp</a> for the Easter Season!🐰 <br> <br>
Your objective is to catch as many falling, colorful eggs as possible flying as the Easter Bunny in the flying Easter Basket 🧺
</p>

<h2 align="center">
    ✨ Getting Started! ✨
</h2>
<ol type="A">
    <li> <strong>Prerequesites:</strong>
        <ul type="disc">
            <li> <strong>CMake:</strong> <a href="https://cmake.org/">https://cmake.org/</a>
            <li> <strong>GCC Toolchain:</strong> <a href="https://gcc.gnu.org/">https://gcc.gnu.org/</a>
            <li> <strong>Git:</strong> <a href="https://git-scm.com/">https://git-scm.com/</a>
        </ul>
    <li> <strong>Manual Installation:</strong>
        <ol type="1">
            <li> Open the <strong> RELEASE </strong> page from this repository / open the <strong><a href="https://itsyakub.itch.io/easter-hunt">Itch.io</a></strong> page.
            <li> Select your desired release.
            <li> Unzip the archive file.
            <li> Navigate to the <strong>/game/</strong> folder inside the downloaded directory.
            <li> Select the executable.
        </ol> 
    </li>
    <li> <strong>Building from scratch:</strong>
        <ol type="1">
            <li> Clone the <strong><a href="https://github.com/itsYakub/Easter-Hunt">Github Repository</a></strong></strong>.
<pre>
git clone https://github.com/itsYakub/Easter-Hunt.git --depth=1 --branch=main
</pre>
            <li> Go to the project's directory: 
<pre>
cd Easter-Hunt
</pre>
            <li> Pull the submodules: <br>
<pre>
git submodule update --init
</pre>
            <li> Build raylib-cpp: <br>
<pre>
cd lib/raylib
mkdir bin
cd bin
cmake .. -G "Unix Makefiles"
cmake --build .
</pre>
            <li> Go back to the main project directory and build the game: <br>
<pre>
cd ../../..
mkdir bin
cd bin
cmake .. -G "Unix Makefiles"
cmake --build .
</pre>
            <li> Run the executable.
        </ol>
    </li>
</ol>

<h2 align="center">
    🎮 Controls 🎮
</h2>
<table align="center">
    <thead>
        <tr>
            <th> Input </th>
            <th> Action </th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td> <kbd>Space</kbd> <kbd>W</kbd> <kbd> ↑ </kbd> </td>
            <td> Move Up </td>
        </tr>
        <tr>
            <td> <kbd>A</kbd> <kbd>←</kbd> </td>
            <td> Move Left </td>
        </tr>
        <tr>
            <td> <kbd>D</kbd> <kbd>→</kbd> </td>
            <td> Move Right </td>
        </tr>
    </tbody>
<table>

<h2 align="center">
    📖 Credits 📖
</h2>
<ul type="disc">
    <li> <strong>RobLoach/raylib-cpp: </strong><br>
    <a href="https://github.com/RobLoach/raylib-cpp/tree/master ">https://github.com/RobLoach/raylib-cpp/tree/master </a>
    <li> <strong>Vanilla Milkshake Palette: </strong><br>
     <a href="https://lospec.com/palette-list/vanilla-milkshake">https://lospec.com/palette-list/vanilla-milkshake</a>
    <li> <strong>Egg SFX: </strong><br>
    <a href="https://www.soundsnap.com/tags/egg">https://www.soundsnap.com/tags/egg</a>
    <li> <strong>raysan5/rfxgen: </strong><br>
    <a href="https://raylibtech.itch.io/rfxgen">https://raylibtech.itch.io/rfxgen</a>
    <li> <strong>Background OST: </strong><br>
    <a href="https://soundcloud.com/dream-story-studio">https://soundcloud.com/dream-story-studio</a>
    <li> <strong>Varela Round font: </strong><br>
    <a href="https://fonts.google.com/specimen/Varela+Round">https://fonts.google.com/specimen/Varela+Round</a>
    <li> <strong>Figma: </strong><br>
    <a href="https://www.figma.com">https://www.figma.com</a>
</ul>

<h2 align="center">
    ❗ LICENCE ❗
</h2>
<p align="center">
    This project is under the <strong><a href="https://github.com/itsYakub/Easter-Hunt/blob/main/LICENCE">MIT Licence</a></strong>
</p>