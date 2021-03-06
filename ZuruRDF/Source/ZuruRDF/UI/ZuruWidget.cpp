
// ==================================================================== //

#include "ZuruWidget.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* ZURU WIDGET                                                          */
/************************************************************************/

void UZuruWidget::Bind(APlayerController& InPlayerController)
{

}

void UZuruWidget::Bind(APawn& InPawn)
{

}

void UZuruWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();

    OnConstructed.Broadcast();
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION