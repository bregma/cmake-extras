#include <memory>
#include <glib.h>
#include <libintl.h>

using namespace std;

namespace {

static inline char* _(const char *__msgid) {
    return gettext(__msgid);
}

static inline shared_ptr<char> get_string(char* s) {
    return shared_ptr<char>(s, &g_free);
}

static void translations() {
    shared_ptr<GKeyFile> gkf(g_key_file_new(), &g_key_file_free);

    GError* error = NULL;
    if (!g_key_file_load_from_file(gkf.get(), CONFIG_FILE, G_KEY_FILE_NONE, &error)) {
        g_warning("Could not read config file '%s': %s", CONFIG_FILE, error->message);
        g_error_free(error);
        g_test_fail();
        return;
    }

    shared_ptr<char> tmp;

    // DisplayName translated through INI file
    tmp = get_string(g_key_file_get_locale_string(gkf.get(), "Config", "DisplayName", NULL, NULL));
    g_assert_cmpstr(tmp.get(), ==, "FooApp translated");

    // DisplayName translated through gettext
    tmp = get_string(g_key_file_get_string(gkf.get(), "Config", "DisplayName", NULL));
    g_assert_cmpstr(gettext(tmp.get()), ==, "FooApp translated");

    // Description translated through INI file
    tmp = get_string(g_key_file_get_locale_string(gkf.get(), "Config", "Description", NULL, NULL));
    g_assert_cmpstr(tmp.get(), ==, "FooApp is really great translated");

    // Description translated through gettext
    tmp = get_string(g_key_file_get_string(gkf.get(), "Config", "Description", NULL));
    g_assert_cmpstr(gettext(tmp.get()), ==, "FooApp is really great translated");

    // Plain gettext translation from extracted string in this .cpp file
    g_assert_cmpstr(_("Hello FooApp!"), ==, "Hello translated FooApp!");
}

}

int main(int argc, char** argv) {
    setenv("LANG", LANGUAGE, TRUE);

    unsetenv("LC_ALL");
    unsetenv("GDM_LANG");
    unsetenv("LANGUAGE");

    setlocale(LC_ALL, LANGUAGE);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    bindtextdomain(GETTEXT_PACKAGE, LOCALE_DIR);
    textdomain(GETTEXT_PACKAGE);

    g_test_init (&argc, &argv, NULL);
    g_test_add_func("/intltool-demo/translations", translations);

    return g_test_run();
}
