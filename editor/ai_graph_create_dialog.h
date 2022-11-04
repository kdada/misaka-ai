#ifndef AI_GRAPH_CREATE_DIALOG_H
#define AI_GRAPH_CREATE_DIALOG_H

#include "scene/gui/dialogs.h"

class EditorFileDialog;
class LineEdit;
class AIGraphCreateDialog : public ConfirmationDialog {
    GDCLASS(AIGraphCreateDialog, ConfirmationDialog);

private:
    EditorFileDialog *editor_file_dialog;
    LineEdit *file_path;
    Button *path_button;

    void _browse_path();
    void _file_selected(const String &p_file);
    void _update_theme();

protected:
	void _notification(int p_what);

public:
    AIGraphCreateDialog();
};

#endif // AI_GRAPH_CREATE_DIALOG_H