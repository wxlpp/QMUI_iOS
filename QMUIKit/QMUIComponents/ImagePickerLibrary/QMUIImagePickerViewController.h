//
//  QMUIImagePickerViewController.h
//  qmui
//
//  Created by Kayo Lee on 15/5/2.
//  Copyright (c) 2015年 QMUI Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QMUICommonViewController.h"
#import "QMUIImagePickerPreviewViewController.h"
#import "QMUIAsset.h"
#import "QMUIAssetsGroup.h"

@class QMUIImagePickerViewController;
@class QMUIButton;

@protocol QMUIImagePickerViewControllerDelegate <NSObject>

@optional

/**
 *  创建一个 ImagePickerPreviewViewController 用于预览图片
 */
- (QMUIImagePickerPreviewViewController *)imagePickerPreviewViewControllerForImagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController;

/**
 *  控制照片的排序，若不实现，默认为 QMUIAlbumSortTypePositive
 *  @note 注意返回值会决定第一次进来相片列表时列表默认的滚动位置，如果为 QMUIAlbumSortTypePositive，则列表默认滚动到底部，如果为 QMUIAlbumSortTypeReverse，则列表默认滚动到顶部。
 */
- (QMUIAlbumSortType)albumSortTypeForImagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController;

/**
 *  多选模式下选择图片完毕后被调用（点击 sendButton 后被调用），单选模式下没有底部发送按钮，所以也不会走到这个delegate
 *
 *  @param imagePickerViewController 对应的 QMUIImagePickerViewController
 *  @param imagesAssetArray          包含被选择的图片的 QMUIAsset 对象的数组。
 */
- (void)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController didFinishPickingImageWithImagesAssetArray:(NSMutableArray<QMUIAsset *> *)imagesAssetArray;

/**
 *  cell 被点击时调用（先调用这个接口，然后才去走预览大图的逻辑），注意这并非指选中 checkbox 事件
 *
 *  @param imagePickerViewController        对应的 QMUIImagePickerViewController
 *  @param imageAsset                       被选中的图片的 QMUIAsset 对象
 *  @param imagePickerPreviewViewController 选中图片后进行图片预览的 viewController
 */
- (void)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController didSelectImageWithImagesAsset:(QMUIAsset *)imageAsset afterImagePickerPreviewViewControllerUpdate:(QMUIImagePickerPreviewViewController *)imagePickerPreviewViewController;

/// 是否能够选中 checkbox
- (BOOL)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController shouldCheckImageAtIndex:(NSInteger)index;

/// 即将选中 checkbox 时调用
- (void)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController willCheckImageAtIndex:(NSInteger)index;

/// 选中了 checkbox 之后调用
- (void)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController didCheckImageAtIndex:(NSInteger)index;

/// 即将取消选中 checkbox 时调用
- (void)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController willUncheckImageAtIndex:(NSInteger)index;

/// 取消了 checkbox 选中之后调用
- (void)imagePickerViewController:(QMUIImagePickerViewController *)imagePickerViewController didUncheckImageAtIndex:(NSInteger)index;

/**
 *  取消选择图片后被调用
 */
- (void)imagePickerViewControllerDidCancel:(QMUIImagePickerViewController *)imagePickerViewController;

/**
 *  即将需要显示 Loading 时调用
 *
 *  @see shouldShowDefaultLoadingView
 */
- (void)imagePickerViewControllerWillStartLoading:(QMUIImagePickerViewController *)imagePickerViewController;

/**
 *  即将需要隐藏 Loading 时调用
 *
 *  @see shouldShowDefaultLoadingView
 */
- (void)imagePickerViewControllerDidFinishLoading:(QMUIImagePickerViewController *)imagePickerViewController;

@end


@interface QMUIImagePickerViewController : QMUICommonViewController<UICollectionViewDataSource, UICollectionViewDelegate, QMUIImagePickerPreviewViewControllerDelegate>

@property(nonatomic, nullable, weak) id<QMUIImagePickerViewControllerDelegate> imagePickerViewControllerDelegate;

/// 图片的最小尺寸，布局时如果有剩余空间，会将空间分配给图片大小，所以最终显示出来的大小不一定等于minimumImageWidth。默认是75。
@property(nonatomic, assign) CGFloat minimumImageWidth UI_APPEARANCE_SELECTOR;

@property(nonatomic, strong, readonly) UICollectionViewFlowLayout *collectionViewLayout;
@property(nonatomic, strong, readonly) UICollectionView *collectionView;

@property(nonatomic, strong, readonly) UIView *operationToolBarView;
@property(nonatomic, strong, readonly) QMUIButton *previewButton;
@property(nonatomic, strong, readonly) QMUIButton *sendButton;
@property(nonatomic, strong, readonly) UILabel *imageCountLabel;

/// 也可以直接传入 QMUIAssetsGroup，然后读取其中的 QMUIAsset 并储存到 imagesAssetArray 中，传入后会赋值到 QMUIAssetsGroup，并自动刷新 UI 展示
- (void)refreshWithAssetsGroup:(QMUIAssetsGroup *)assetsGroup;

@property(nonatomic, strong, readonly) NSMutableArray<QMUIAsset *> *imagesAssetArray;
@property(nonatomic, strong, readonly) QMUIAssetsGroup *assetsGroup;

/// 当前被选择的图片对应的 QMUIAsset 对象数组
@property(nonatomic, strong, readonly) NSMutableArray<QMUIAsset *> *selectedImageAssetArray;

/// 是否允许图片多选，默认为 YES。如果为 NO，则不显示 checkbox 和底部工具栏。
@property(nonatomic, assign) BOOL allowsMultipleSelection;

/// 最多可以选择的图片数，默认为无符号整形数的最大值，相当于没有限制
@property(nonatomic, assign) NSUInteger maximumSelectImageCount;

/// 最少需要选择的图片数，默认为 0
@property(nonatomic, assign) NSUInteger minimumSelectImageCount;

/// 选择图片超出最大图片限制时 alertView 的标题
@property(nonatomic, copy) NSString *alertTitleWhenExceedMaxSelectImageCount;

/// 选择图片超出最大图片限制时 alertView 底部按钮的标题
@property(nonatomic, copy) NSString *alertButtonTitleWhenExceedMaxSelectImageCount;

/**
 *  加载相册列表时会出现 loading，若需要自定义 loading 的形式，可将该属性置为 NO，默认为 YES。
 *  @see imagePickerViewControllerWillStartLoading: & imagePickerViewControllerDidFinishLoading:
 */
@property(nonatomic, assign) BOOL shouldShowDefaultLoadingView;

@end


@interface QMUIImagePickerViewController (UIAppearance)

+ (nonnull instancetype)appearance;

@end
