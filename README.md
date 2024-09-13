## Attention
This game engine is highly experimental, so much so the few libraries it uses
is using features and bugs fixed only available on either direct from the repos
or forks, so make sure to run:
```
git submodule init
git submodule update
```

This will change once the features are out in releases.

If you are having issues with gcc-13 do like me and use the highest available
version of clang that you are able to install.

We also use [SEMVER](https://semver.org/) versioning system so consider this
engine an alpha before 0.8 and beta before 1.0.

# Clockwork Reverie

Hello, this will be a 2D and 3D game engine made from scratch, with as few
libraries as possible.

Why?
For learning purposes and because so far the majority of game engines I used
let me down somewhat.

# FAQ

1. Is this engine ready to use?

   R: Absolutely not, and will not be for a couple years yet.

2. Why Python? Python is slow!

   R: Is it really? I have seen code that is quicker to execute in Python than
   in C++, it depends completely in how you code, and since the engine itself
   is entirely made with C++, any performance bottle necks coming from Python
   gets diminished quite a bit.

3. Anyone can see my source code with Python!

   R: You can create your game with C++ too if you'd like.
