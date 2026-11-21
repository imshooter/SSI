# SSI\version

```pawn
#include <SSI\version>
```

## Quick Start

The version shared by the SSI libraries and their startup banner. Define
`SSI_NO_BANNER` before including SSI to keep the version without the banner.

JIT detection uses `OnJITCompile`, as the legacy JIT plugin reports it.
Components that do not raise that callback are shown as `not reported`.
