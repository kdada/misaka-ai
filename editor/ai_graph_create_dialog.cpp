#include "ai_graph_create_dialog.h"
#include "scene/gui/grid_container.h"
#include "scene/gui/option_button.h"
#include "scene/gui/line_edit.h"
#include "editor/editor_file_dialog.h"
#include "core/config/project_settings.h"

void AIGraphCreateDialog::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_update_theme();
		} break;

		case NOTIFICATION_THEME_CHANGED: {
			_update_theme();
		} break;
	}
}

void AIGraphCreateDialog::_update_theme() {
	path_button->set_icon(get_theme_icon(SNAME("Folder"), SNAME("EditorIcons")));
}

void AIGraphCreateDialog::_browse_path() {
	editor_file_dialog->set_file_mode(EditorFileDialog::FILE_MODE_SAVE_FILE);
	editor_file_dialog->set_title(TTR("Open AI Graph / Choose Location"));
	editor_file_dialog->set_ok_button_text(TTR("Open"));

	editor_file_dialog->set_disable_overwrite_warning(true);
	editor_file_dialog->clear_filters();
	editor_file_dialog->add_filter("*.tres");
    editor_file_dialog->set_current_path(file_path->get_text());

	editor_file_dialog->popup_file_dialog();
}

void AIGraphCreateDialog::_file_selected(const String &p_file) {
	String p = ProjectSettings::get_singleton()->localize_path(p_file);
	file_path->set_text(p);

	String filename = p.get_file().get_basename();
	int select_start = p.rfind(filename);
	file_path->select(select_start, select_start + filename.length());
	file_path->set_caret_column(select_start + filename.length());
	file_path->grab_focus();
}

AIGraphCreateDialog::AIGraphCreateDialog() {
    GridContainer *grid_container = memnew(GridContainer);
    grid_container->set_columns(2);
    add_child(grid_container);

    grid_container->add_child(memnew(Label(TTR("Template:"))));
    OptionButton *template_option_buttion = memnew(OptionButton);
    template_option_buttion->add_item(TTR("Empty"));
    template_option_buttion->add_item(TTR("FSM"));
    template_option_buttion->add_item(TTR("BT"));
    template_option_buttion->add_item(TTR("GOAP"));
    grid_container->add_child(template_option_buttion);

    grid_container->add_child(memnew(Label(TTR("Path:"))));
	HBoxContainer *hbox_container = memnew(HBoxContainer);
	hbox_container->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	file_path = memnew(LineEdit);
	file_path->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	hbox_container->add_child(file_path);
	path_button = memnew(Button);
	path_button->connect("pressed", callable_mp(this, &AIGraphCreateDialog::_browse_path));
	hbox_container->add_child(path_button);
    hbox_container->set_custom_minimum_size(Size2(300,0));
	grid_container->add_child(hbox_container);

    editor_file_dialog = memnew(EditorFileDialog);
	editor_file_dialog->connect("file_selected", callable_mp(this, &AIGraphCreateDialog::_file_selected));
	editor_file_dialog->set_file_mode(EditorFileDialog::FILE_MODE_OPEN_FILE);
	add_child(editor_file_dialog);

	set_ok_button_text(TTR("Create"));
	set_hide_on_ok(false);
	set_title(TTR("Create AI Graph"));
}