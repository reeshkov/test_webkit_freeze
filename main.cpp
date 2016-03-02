#include "myobj.h"
#include <QApplication>

#include <QDebug>

#include <QMainWindow>
#include <QWebView>
#include <QWebInspector>
#include <QWebFrame>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setObjectName("Main");

  QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true); // DEBUG
  QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);

  QWebView *view = new QWebView();
  view->resize(300, 300);
  view->setObjectName("view");
  // for freeze presentation
  view->page()->mainFrame()->setHtml("<!DOCTYPE html><html><head><style> \
                                     div { \
                                         width: 100px; \
                                         height: 100px; \
                                         background-color: red; \
                                         position: relative; \
                                         -webkit-animation-name: example; \
                                         -webkit-animation-duration: 4s; \
                                         -webkit-animation-iteration-count: infinite; \
                                     } \
                                     @-webkit-keyframes example { \
                                         0%   {background-color:red; left:0px; top:0px;} \
                                         25%  {background-color:yellow; left:200px; top:0px;} \
                                         50%  {background-color:blue; left:200px; top:200px;} \
                                         75%  {background-color:green; left:0px; top:200px;} \
                                         100% {background-color:red; left:0px; top:0px;} \
                                     } \
                                     </style></head><body><div></div></body></html>");
  view->show();
  QWebInspector *inspector = new QWebInspector; // DEBUG
  inspector->setObjectName("inspector");
  inspector->setPage(view->page()); // DEBUG
  inspector->show(); // DEBUG

  // Question main:
  QObject *custom = new MyObj();

  QThread *errProduse = new QThread(&a);
  errProduse->setObjectName("errProduse");
  errProduse->start();
  custom->moveToThread(errProduse);

  view->page()->mainFrame()->addToJavaScriptWindowObject("myObject", custom); // , QScriptEngine::ScriptOwnership);

  // question about:
  view->page()->mainFrame()->evaluateJavaScript( "myObject.mySignal.connect(function(){console.warn('mySignal emitted')});" ); // generate error
//  view->page()->mainFrame()->evaluateJavaScript( "myObject.mySignal();" ); // kill app

  return a.exec();
}
