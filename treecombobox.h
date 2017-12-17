#include <QtGui>
#include <QComboBox>
#include <QTreeView>

class TreeComboBox : public QComboBox
{
public:
	TreeComboBox(QWidget* parent = 0) : QComboBox(parent), skipNextHide(false)
	{
        _internal_tree_view = new QTreeView(this);
        setView(_internal_tree_view);
		view()->viewport()->installEventFilter(this);
	}

	bool eventFilter(QObject* object, QEvent* event)
	{
		if (event->type() == QEvent::MouseButtonPress && object == view()->viewport())
		{
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			QModelIndex index = view()->indexAt(mouseEvent->pos());
			if (!view()->visualRect(index).contains(mouseEvent->pos()))
				skipNextHide = true;
		}
		return false;
	}

	virtual void showPopup()
	{
		setRootModelIndex(QModelIndex());
		QComboBox::showPopup();
	}

	virtual void hidePopup()
	{
		setRootModelIndex(view()->currentIndex().parent());
		setCurrentIndex(view()->currentIndex().row());
		if (skipNextHide)
			skipNextHide = false;
		else
			QComboBox::hidePopup();
	}
    QTreeView* _internal_tree_view;
private:
	bool skipNextHide;
};
