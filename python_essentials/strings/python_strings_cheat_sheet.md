# Python Strings — Industry Cheat Sheet

Concise, practical notes for day‑to‑day use. Copy/paste the snippets.

---

## 0) Core ideas
- **Immutable**: operations return new strings; don’t modify in place.
- **Literals**: `'single'`, `"double"`, `'''multi
line'''`, raw `r"C:\path"` (no escape processing).
- **Byte strings**: `b"..."` are `bytes` (not `str`).
- **F‑strings** (3.6+): `f"Hello {name}!"` with format specs.

```python
s = "naïve café ☕"
len(s)             # counts code points, not user‑perceived characters (graphemes)
"caf" in s         # membership
s[0], s[-1]        # indexing
s[1:4], s[::-1]    # slicing & reverse
```

---

## 1) Choosing single vs double quotes
- **Identical meaning/perf**. Choose based on readability and style.
- Use the **opposite** of the quote that appears inside to avoid escaping.
- Follow team tools: formatters like **Black** prefer double quotes unless escaping would increase.
- Docstrings conventionally use triple **double** quotes.

```python
s1 = "He said, 'Hello!'"
s2 = 'She replied, "Hi!"'
```

---

## 2) Building strings efficiently
- Prefer **`"".join(parts)`** over `+=` in loops.
- For many writes, use `io.StringIO`.

```python
" ".join(["fast", "join"])               # 'fast join'
from io import StringIO
buf = StringIO()
for i in range(3): buf.write(str(i))
result = buf.getvalue()                  # '012'
```

---

## 3) Search, split, and slice
```python
s = "key=value=value2"
s.find("val")           # 4  (−1 if not found)
s.rfind("=")            # last occurrence
s.count("=")            # 2
s.startswith("key"), s.endswith("2")

s.split("=")            # ['key','value','value2']
s.rsplit("=", 1)        # ['key=value', 'value2']
s.partition("=")        # ('key','=', 'value=value2')
s.rpartition("=")       # ('key=value','=', 'value2')

"a
b
c".splitlines()    # ['a','b','c'] (universal newlines)
```

---

## 4) Clean & transform
```python
s = "  --hello--  "
s.strip(" -")            # 'hello'
s.lstrip(), s.rstrip()

"hello world".replace(" ", "-")        # 'hello-world'

# Prefix/suffix (3.9+)
"log_2025".removeprefix("log_")        # '2025'
"file.txt".removesuffix(".txt")        # 'file'

# Character‑wise translation
tr = str.maketrans({ord("_"):"-", ord(" "):None})
"a_b c".translate(tr)                   # 'a-bc'
```

---

## 5) Case & comparisons
```python
s.lower(), s.upper(), s.title(), s.capitalize()
# Robust, locale‑agnostic case‑folding for comparisons
"straße".casefold() == "STRASSE".casefold()  # True

# Constant‑time compare for secrets
import hmac
hmac.compare_digest("tokenA", "tokenB")
```

---

## 6) Formatting with f‑strings
```python
n = 12345.678
f"{n:,.2f}"        # '12,345.68'
f"{n:=010.1f}"     # zero‑pad + alignment -> '00012345.7'
ratio = 0.2378; f"{ratio:.1%}"  # '23.8%'
name = "Ada"; f"Hello {name!r}" # uses repr -> "'Ada'"

# Align within width
f"[{name:^10}]"    # centered
f"[{name:<10}]"    # left
f"[{name:>10}]"    # right

from datetime import datetime
now = datetime(2025,8,12,15,30)
f"{now:%Y-%m-%d %H:%M}"   # '2025-08-12 15:30'
```

---

## 7) Regular expressions (quick essentials)
```python
import re
m = re.search(r"(\w+)-(\d+)", "task-42")
if m:
    m.group(0), m.group(1), m.group(2)
# -> ('task-42','task','42')

re.findall(r"\b\w{3}\b", "yes we can")  # ['yes', 'can']
re.sub(r"\s+", " ", "a   b\n c")         # 'a b c'

# Precompile if reused
pat = re.compile(r"^id:(\d+)$")
bool(pat.match("id:123"))
```
> Tip: use `re` for complex patterns; prefer `csv`, `urllib.parse`, etc. for structured data.

---

## 8) Unicode, accents, and normalization
```python
import unicodedata as ud
s = "Café"; n = ud.normalize("NFC", s)  # compose accents
# Remove accents (basic):
"".join(c for c in ud.normalize("NFD", s) if ud.category(c) != "Mn")  # 'Cafe'
```
- Use `.casefold()` for caseless matching; `.lower()` isn’t enough in some languages.
- `len()` counts code points; user‑perceived characters (emoji + skin tone, flags) may be multiple code points.

---

## 9) Encoding & bytes
```python
b = "Café".encode("utf-8")           # bytes
"Café".encode("ascii", "ignore")     # b'Caf'
"Caf\xe9".encode("latin1").decode("utf-8", "replace")  # 'Caf�'

b.decode("utf-8")
```
- Prefer **UTF‑8**. Specify errors: `'strict'` (default), `'ignore'`, `'replace'`, `'backslashreplace'`.
- **Bytes vs repr vs decoded**:
  - **Actual bytes** = integers 0–255.
  - **Python representation** = `b'...'` with `\xhh` escapes for non‑ASCII.
  - **Decoded text** = `bytes.decode("utf-8")` → `str`.

```python
data = b"Caf\xc3\xa9"    # actual bytes for 'Café' (UTF‑8)
print(data)                # b'Caf\xc3\xa9'  ← repr
print(data.decode("utf-8"))# Café             ← human text
```

---

## 10) When NOT to use string ops (use libraries)
- **Paths**: `from pathlib import Path` (`Path("a") / "b.txt"`).
- **URLs**: `from urllib.parse import urlparse, parse_qs, urljoin`.
- **CSV/TSV**: `import csv` instead of `split(',')`.
- **JSON**: `json.dumps(obj, ensure_ascii=False)` (don’t hand‑build JSON).
```python
from pathlib import Path
p = Path("/var") / "log" / "sys.log"; p.suffix  # '.log'
```

---

## 11) HTML, shell, SQL safety
```python
import html, shlex
html.escape("<b> & ' ")         # escape for HTML
shlex.quote("weird arg & stuff")# safe shell quoting

# SQL: always parameterize (example with sqlite3)
import sqlite3
c = sqlite3.connect(":memory:").cursor()
user = "O'Reilly"
c.execute("SELECT * FROM users WHERE name = ?", (user,))
```

---

## 12) Handy snippets
```python
# Truncate with ellipsis
s = "very long line"; maxw = 10
s if len(s) <= maxw else s[:maxw-1] + "…"

# Slugify (basic)
import re, unicodedata as ud
slug = "".join(c for c in ud.normalize("NFD", "Hello, World!") if ud.category(c) != "Mn")
slug = re.sub(r"[^\w\s-]", "", slug).strip().lower()
slug = re.sub(r"[\s_-]+", "-", slug)  # 'hello-world'

# Simple pluralization
n = 3; f"{n} file{'s' if n != 1 else ''}"

# Zero‑padding IDs
f"UID-{42:06d}"   # 'UID-000042'

# Count substrings (non‑overlapping)
"banana".count("ana")    # 1

# Center/align/pad
"hi".center(6, '-')      # '--hi--'
```

---

## 13) Pitfalls to remember
- `strip(chars)` removes **any** of those characters at ends, not the substring.
- `str.isdigit()` vs `str.isdecimal()` vs `str.isnumeric()` differ; prefer `str.isdigit()` for ASCII digits.
- Avoid `+=` in hot loops; use `join` or `StringIO`.
- Don’t assume `lower()` is enough for case‑insensitive compare; use `casefold()`.
- Be wary of grapheme clusters (emoji, flags) when slicing user‑visible text.

---

## 14) Most‑used methods (quick list)
`strip`, `split/rsplit/splitlines`, `join`, `replace`, `find/rfind`, `startswith/endswith`, `count`, `lower/upper/casefold`, `removeprefix/removesuffix`, `center/ljust/rjust/zfill`, `format`/f‑strings.

---

## 15) Slice Tricks (works for any sequence)
```python
sequence[start:stop:step]
```
- `start` → index to begin (default depends on step)
- `stop`  → index to end (exclusive)
- `step`  → increment (negative = go backwards)

**Common patterns**
```python
s = "abcdefgh"

s[::-1]      # reverse -> 'hgfedcba'
s[::2]       # every 2nd char -> 'aceg'
s[1::2]      # odd-indexed chars -> 'bdfh'
s[:5]        # first 5 chars -> 'abcde'
s[5:]        # from index 5 to end -> 'fgh'
s[-3:]       # last 3 chars -> 'fgh'
s[:-3]       # everything except last 3 -> 'abcde'

# Negative steps for partial reversals
s[5:1:-1]    # reverse from index 5 to just after index 1 -> 'fedc'
```

**Use cases**
```python
word == word[::-1]   # palindrome check
text[::2]            # even positions
text[1::2]           # odd positions
seq[:n][::-1]        # reverse only first n elements
[i:i+3] for i in range(0, len(s), 3)  # chunking with slices
```

---

## 16) Bytes refresher (0–255)
- A **byte** is 8 bits → 2^8 = **256** values → integers **0..255**.
```python
b = b"Caf\xc3\xa9"
list(b)  # [67, 97, 102, 195, 169]
```
- `str` = Unicode code points (text). `bytes` = raw bytes (data). Encode/decode explicitly.
