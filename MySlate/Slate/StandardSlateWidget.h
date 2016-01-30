#pragma once
#include "StandardHUD.h"
#include "SlateBasics.h"

class SStandardSlateWidget : public SCompoundWidget
{
	FOnClicked OnConfirm; //����ָ��


	SLATE_BEGIN_ARGS(SStandardSlateWidget) {}

	/*See private declaration of OwnerHUD below.*/
	SLATE_ARGUMENT(TWeakObjectPtr<class AStandardHUD>, OwnerHUD)
	SLATE_ARGUMENT(FOnClicked, OnConfirmClicked) //���ⲿ����һ������ָ�����

		SLATE_END_ARGS()

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Needed for every widget
	/////Builds this widget and any of it's children
	void Construct(const FArguments& InArgs);

	FReply OnClicked();
	void OnPressed();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

private:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pointer to our parent HUD
	/////To make sure HUD's lifetime is controlled elsewhere, use "weak" ptr.
	/////HUD has "strong" pointer to Widget,
	/////circular ownership would prevent/break self-destruction of hud/widget (cause memory leak).
	TWeakObjectPtr<class AStandardHUD> OwnerHUD;

	//Buttons
	TSharedPtr<SButton> RefreshButton;
	TSharedPtr<STextBlock> RefreshButtonText;
	TSharedPtr<SButton> ClearTileButton;

	//����style
	TSharedPtr<STextBlock> TestStyleText;
	const struct FGlobalStyle* MenuStyle;

	//�������ݰ�
	TAttribute<FText> Score;
	TAttribute<FText> Health;
	float _scoreCounter;
	float _healthCounter;
	FText GetScore() const;
	FText GetHealth() const;
	bool _bStop;
};