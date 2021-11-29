def windows_select(yay, nay):
    return select({
            "//conditions:default": nay,
            })
