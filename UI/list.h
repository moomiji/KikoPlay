#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QTreeView>
#include <QVBoxLayout>
#include <QAction>
#include <QActionGroup>
#include <QWidgetAction>
#include <QStackedLayout>
#include <QToolButton>
#include <QLineEdit>
#include <QRegExp>
#include <QStyledItemDelegate>
#include "Common/notifier.h"
struct DanmuComment;
class FilterBox : public QLineEdit
{
    Q_OBJECT
public:
    enum SearchType
    {
        Title, FilePath
    };
    explicit FilterBox(QWidget *parent = nullptr);
    inline Qt::CaseSensitivity caseSensitivity() const
    {
        return actCaseSensitivity->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    }
    inline QRegExp::PatternSyntax patternSyntax() const
    {
        return static_cast<QRegExp::PatternSyntax>(patternGroup->checkedAction()->data().toInt());
    }
    inline SearchType searchType() const
    {
        return static_cast<SearchType>(searchTypeGroup->checkedAction()->data().toInt());
    }
signals:
    void filterChanged();
private:
    QAction *actCaseSensitivity;
    QActionGroup *patternGroup, *searchTypeGroup;
};
class ListWindow : public QWidget, public NotifyInterface
{
    Q_OBJECT
public:
    explicit ListWindow(QWidget *parent = nullptr);    
private:
    void initActions();
    inline QModelIndex getPSParentIndex();
    inline QSharedPointer<DanmuComment> getSelectedDanmu();
    void matchPool(const QString &scriptId = "");

    QWidget *infoTip;

    QTreeView *playlistView;
    QToolButton *playlistPageButton,*danmulistPageButton;
    QStackedLayout *contentStackLayout;
    QAction *act_play,*act_addCollection,*act_addItem,*act_addFolder,
            *act_cut,*act_paste,*act_moveUp,*act_moveDown,*act_merge,
            *act_remove,*act_clear, *act_removeMatch, *act_removeInvalid,
            *act_sortSelectionAscending,*act_sortSelectionDescending,*act_sortAllAscending,*act_sortAllDescending,
            *act_noLoopOne,*act_noLoopAll,*act_loopOne,*act_loopAll,*act_random,
            *act_browseFile,*act_autoMatch,*act_exportDanmu,*act_addWebDanmuSource, *act_addLocalDanmuSource, *act_updateDanmu,
            *act_sharePoolCode, *act_shareResourceCode, *act_autoMatchMode, *act_markBgmCollection, *act_updateFolder, *act_PlayOnOtherDevices;
    QMenu *matchSubMenu, *markSubMenu;
    bool actionDisable;
    QActionGroup *loopModeGroup;
    int matchStatus;
    QWidget *setupPlaylistPage();

    QTreeView *danmulistView;
    QWidget *setupDanmulistPage();
    QAction *act_addOnlineDanmu,*act_addLocalDanmu,*act_editPool,*act_editBlock,
            *act_copyDanmuText,*act_copyDanmuColor,*act_copyDanmuSender,
            *act_blockText,*act_blockColor,*act_blockSender,
            *act_jumpToTime, *act_deleteDanmu;


protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
public slots:
    void sortSelection(bool allItem,bool ascending);
    void playItem(const QModelIndex &index,bool playChild=true);

    virtual void showMessage(const QString &msg, int flag);
    void updatePlaylistActions();
    void updateDanmuActions();
    int updateCurrentPool();
    void infoCancelClicked();
};

#endif // LISTWINDOW_H
