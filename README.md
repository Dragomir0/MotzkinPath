  # MotzkinPath

  In combinatorics, a **Motzkin path** is a path of length `n` that can be traced on a grid following these constraints:

  ## Allowed moves:
  - ↗️ `u` (*up*): step northeast `(1,1)`
  - ➡️ `r` (*right*): step east `(1,0)`
  - ↘️ `d` (*down*): step southeast `(1,-1)`

  ## Constraints:
  * The path must start at point `(0,0)`
  * The path must end at point `(n,0)`
  * The path must never go below the line segment connecting `(0,0)` and `(n,0)`

  Motzkin paths of length 4 example (from [Wikipedia](https://en.wikipedia.org/wiki/Motzkin_number)):

  ![Motzkin paths of length 4](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/Motzkin4.svg/1280px-Motzkin4.svg.png)

  The program can be invoked with the following syntax:

```sh
./motzkin LETTERS
```
  Where LETTERS is a sequence of characters from the set {u, d, r} and generates an SVG file printed to stdout, representing the corresponding Motzkin path, with moves interpreted as follows:

  ## Examples

```sh
./motzkin urudd > urudd.svg
```

  ![Le chemin de Motzkin `urudd`](./urudd.svg)

```sh
./motzkin uuuuuuuuuddurrruuuurddrrrdddddduuddddddr > test.svg
```

![Le chemin de Motzkin `uuuuuuuuuddurrruuuurddrrrdddddduuddddddr`](./test.svg)

## 🚀 Installation 

To build and test the project:

```bash
make         
make test    
```

## Error Handling

  If no argument is provided, the program prints

-> `error: wrong number of arguments` 

  If an invalid letter (like a) is used, the program prints 

  -> `"error: unrecognized step a" to stderr`

  If the path is invalid (goes below the horizontal axis or does not end at (n,0)), it prints:

  -> `"error: the path cannot go below the horizontal axis"`

  -> `"error: the path cannot end above the horizontal axis"`

  If the path is too wide (more than 40 units), the program stops with the error:

  -> `"error: the path cannot be wider than 40"`

  Each error is followed by usage instructions and termination.