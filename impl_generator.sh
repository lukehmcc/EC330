#!/usr/bin/env bash
name=$1
header="${name}.h"
impl="${name}.cpp"

cat >"$header" <<EOF
#ifndef ${name^^}_H
#define ${name^^}_H


#endif // ${name^^}_H
EOF

cat >"$impl" <<EOF
#include "$header"

EOF
