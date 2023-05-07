#pragma once

#include "BaseView.h"

class IMainWindow;
class StylesViewModel;

class StylesView : public BaseView
{
public:
    StylesView(IMainWindow* parent);

    // IView methods
    IViewModel* GetViewModel() override;
    void SetViewModel(IViewModel* viewModel) override;

    void Render() override;

    // IViewModelListener methods
    void OnEvent(EVmEvent event) override;

private:
    StylesViewModel* m_viewModel;

    int m_stylesFilterIndex;
};

