#include <QtWidgets>

#include "dragwidget.h"

static QLabel *createDragLabel(const QString &text, QWidget *parent)
{
    QLabel *label = new QLabel(text, parent);
    label->setAutoFillBackground(true);
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Raised);
    return label;
}

static QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }

DragWidget::DragWidget(QWidget *parent, bool secondFileSource)
    : QWidget(parent)
{
    if(secondFileSource){
        QFile dictionaryFile(QStringLiteral(":/dictionary/words2.txt"));
        dictionaryFile.open(QIODevice::ReadOnly);
        QTextStream inputStream(&dictionaryFile);

        while (!inputStream.atEnd()) {
            QString word;
            inputStream >> word;
            if (!word.isEmpty()) {
                QLabel *wordLabel = createDragLabel(word, this);
                wordLabel->move(0, lastPosY);
                wordLabel->show();
                wordLabel->setAttribute(Qt::WA_DeleteOnClose);
                lastPosY += 20;
            }
        }
    }
    else{
        QFile dictionaryFile(QStringLiteral(":/dictionary/words.txt"));
        dictionaryFile.open(QIODevice::ReadOnly);
        QTextStream inputStream(&dictionaryFile);

        while (!inputStream.atEnd()) {
            QString word;
            inputStream >> word;
            if (!word.isEmpty()) {
                QLabel *wordLabel = createDragLabel(word, this);
                wordLabel->move(0, lastPosY);
                wordLabel->show();
                wordLabel->setAttribute(Qt::WA_DeleteOnClose);
                lastPosY += 20;
            }
        }
    }

    list = this->findChildren<QLabel *>();

    setAcceptDrops(true);
    setMinimumSize(400, qMax(200, lastPosY));
    setWindowTitle(tr("Draggable Text"));
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        const QMimeData *mime = event->mimeData();
        QStringList pieces = mime->text().split(QRegularExpression(QStringLiteral("\\s+")),
                             QString::SkipEmptyParts);
        QPoint position(0, lastPosY);

        foreach (const QString &piece, pieces) {
            QLabel *newLabel = createDragLabel(piece, this);
            newLabel->move(position);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);
            list.push_back(newLabel);
            lastPosY += 20;
            position.setY(lastPosY);
        }

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }


        lastPosY = 5;
        qDebug() << "==";

        foreach(QLabel *l, list)
        {
            qDebug() << l->text();
            QPoint pos(0, lastPosY);
            l->move(pos);
            lastPosY += 20;
        }

    } else {
        event->ignore();
    }
    foreach (QWidget *widget, findChildren<QWidget *>()) {
        if (!widget->isVisible())
            widget->deleteLater();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = qobject_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    this->clearMask();

    QPoint hotSpot = event->pos() - child->pos();

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(child->text());
    mimeData->setData(hotSpotMimeDataKey(),
                      QByteArray::number(hotSpot.x()) + ' ' + QByteArray::number(hotSpot.y()));

    qreal dpr = window()->windowHandle()->devicePixelRatio();
    QPixmap pixmap(child->size() * dpr);
    pixmap.setDevicePixelRatio(dpr);
    child->render(&pixmap);

    child->hide();

    int i = list.indexOf(child);
    while(i != -1){
        list.removeAt(i);
        i = list.indexOf(child);
    }

    lastPosY = 5;
    qDebug() << "==";

    foreach(QLabel *l, list)
    {
        qDebug() << l->text();
        QPoint pos(0, lastPosY);
        l->move(pos);
        lastPosY += 20;
    }

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

    if (dropAction == Qt::MoveAction){
        child->close();
    }
}
