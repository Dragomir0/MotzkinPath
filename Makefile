bats = bats/bats-core/bin/bats

# Build
# -----

motzkin: motzkin.c
	gcc -o $@ $<

# Test
# ----

test-motzkin: motzkin motzkin.bats
	$(bats) motzkin.bats

test: test-motzkin
