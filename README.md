```bash
git submodule add https://github.com/garettbass/app include/app
git submodule update --init --recursive
```

```c++
// main.cpp
#include <app/app.hpp>

int app::main(int argc, char* argv[]) {
    app::window* window = app::window::create("hello world");

    app::activate();
    window->activate();

    while (app::update(60) and !window->closed());
    delete window;

    return 0;
}
```