def empty_file_rule_impl(ctx):
    ctx.actions.write(
        output = ctx.outputs.out,
        content = "",
        is_executable = False,
    )

empty_file_rule = rule(
    attrs = {
            "out": attr.output(
                    mandatory = True,
            ),
    },
    output_to_genfiles = True,
    implementation = empty_file_rule_impl,
)

def touch(paths):
    for path in paths:
        empty_file_rule(
            name = "gen-file_{}".format(path),
            out = path,
            )


# Rule for simple expansion of template files. This performs a simple
# search over the template file for the keys in substitutions,
# and replaces them with the corresponding values.
#
# Typical usage:
#     load("/tools/build_rules/template_rule", "expand_header_template")
#     template_rule(
#         name = "ExpandMyTemplate",
#         src = "my.template",
#         out = "my.txt",
#         substitutions = {
#             "$VAR1": "foo",
#             "$VAR2": "bar",
#         }
#     )
#
# Args:
#     name: The name of the rule.
#     template: The template file to expand
#     out: The destination of the expanded file
#     substitutions: A dictionary mapping strings to their substitutions

def template_rule_impl(ctx):
    ctx.actions.expand_template(
            template = ctx.file.src,
            output = ctx.outputs.out,
            substitutions = ctx.attr.substitutions,
    )

template_rule = rule(
    attrs = {
            "src": attr.label(
                    mandatory = True,
                    allow_single_file = True,
            ),
            "substitutions": attr.string_dict(mandatory = True),
            "out": attr.output(mandatory = True),
    },
    # output_to_genfiles is required for header files.
    output_to_genfiles = True,
    implementation = template_rule_impl,
)

# Rule for putting creating short files directly in BUILD files.
#
# Typical usage:
#     load("/tools/build_rules/template_rule", "expand_header_template")
#     template_rule(
#         name = "ExpandMyTemplate",
#         src = "my.template",
#         out = "my.txt",
#         substitutions = {
#             "$VAR1": "foo",
#             "$VAR2": "bar",
#         }
#     )
#
# Args:
#     name: The name of the rule.
#     template: The template file to expand
#     out: The destination of the expanded file
#     substitutions: A dictionary mapping strings to their substitutions


def write_file_rule_impl(ctx):
    ctx.actions.write(
        output = ctx.outputs.out,
        content = ctx.attr.content,
        is_executable = ctx.attr.is_executable,
    )

write_file_rule = rule(
    attrs = {
            "out": attr.output(
                    mandatory = True,
                    ),
            "content": attr.string(),
            "is_executable": attr.bool(),
    },
    output_to_genfiles = True,
    implementation = write_file_rule_impl,
)
